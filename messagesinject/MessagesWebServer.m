//
//  MyWebServer.m
//  messagesinject
//
//  Created by Sam Foxman on 7/6/20.
//  Copyright © 2020 organization.name. All rights reserved.
//

#import "MessagesWebServer.h"
#import "Serializer.h"
#import "Logging.h"
#import "MessagesFunctionWrapper.h"

#import <IMCore/IMChat.h>
#import <IMCore/IMChatRegistry.h>
#import <IMCore/IMChatItem.h>

#import <Contacts/Contacts.h>

@implementation MessagesWebServer

#pragma mark init

- (MessagesWebServer*) init {
    self = [super init];
    
    self.activeWebsocketsLock = [NSLock new];
    //websockets are "active" after the initial message has been sent
    self.activeWebsockets = [NSMutableSet new];
    
    return self;
}

#pragma mark initial message

- (NSDictionary*) getInitialMessage {
    //runs on main dispatch queue
    NSMutableArray *chats = [NSMutableArray new];
    
    IMChatRegistry *registry = [IMChatRegistry sharedInstance];
    for (IMChat* chat in [registry allExistingChats]) {
        [chats addObject:[Serializer dictForIMChat:chat]];
    }
    
    //"Because CNContactStore fetch methods perform I/O, it’s recommended that you avoid using the main thread to execute fetches."
    //maybe should change this method to use other thread or something
    CNContactStore *contactStore = [CNContactStore new];
    NSDictionary *contacts = [Serializer dictForCNContactStore:contactStore];
    
    return @{
        @"chats": chats,
        @"contacts": contacts
    };
}

#pragma mark websockets

- (void) addWebSocket:(PSWebSocket*)ws {
    //runs on dispatch main queue
    [self.activeWebsocketsLock lock];
    //lock first to prevent
    //thread 1: getInitialMessage
    //thread 2: imchatItemsDidChange
    //thread 2: broadcast
    //thread 1: sendMessageToWS
    //thread 1: addObject
    //which would leave the websocket that thread 1 just added in an outdated state
    NSDictionary *messageDict = [self getInitialMessage];
    [self sendMessageToWs:ws dict:messageDict type:@"init"];
    [self.activeWebsockets addObject:ws];
    [self.activeWebsocketsLock unlock];
}

-(void) sendMessageToWs:(PSWebSocket*)ws dict:(NSDictionary*)dict type:(NSString*)type {
    NSDictionary *fullMessageDict = @{
        @"type": type,
        @"data": dict
    };
    NSString *jsonStr = [Serializer stringify:fullMessageDict];
    [ws send:jsonStr];
}

/**
 Sends a message to all active websockets
 A websocket is active once the initial message has been sent
 */
-(void) broadcastMessage:(NSDictionary*)dict type:(NSString*)type {
    NSDictionary *fullMessageDict = @{
        @"type": type,
        @"data": dict
    };
    NSString *jsonStr = [Serializer stringify:fullMessageDict];
    [self.activeWebsocketsLock lock];
    for (PSWebSocket *ws in [self activeWebsockets]) {
        [ws send:jsonStr];
    }
    [self.activeWebsocketsLock unlock];
}

-(void) removeWebsocket:(PSWebSocket*)ws {
    [self.activeWebsocketsLock lock];
    [self.activeWebsockets removeObject:ws];
    [self.activeWebsocketsLock unlock];
}

#pragma mark notifications

-(void) imchatPropertiesChanged:(NSNotification*)notification {
    NSDictionary *dict = [Serializer dictForIMChatPropertiesChangedNotification:notification];
    [self broadcastMessage:dict type:@"chatPropertiesChanged"];
}

-(void) imchatItemsDidChange:(NSNotification*)notification {
    NSDictionary *dict = [Serializer dictForIMChatItemsDidChangeNotification:notification];
    [self broadcastMessage:dict type:@"chatItemsDidChange"];
}

#pragma mark handle commands

-(id) safeJsonRead:(NSDictionary*)dict key:(NSString*)key expectedClass:(Class)expectedClass {
    id val = dict[key];
    if (val == nil) {
        [NSException raise:@"MissingValueException" format:@"could not find value for key %@", key];
    }
    /*
    va_list args;
    va_start(args, firstExpectedClass);
    
    Class expectedClass;
    bool valInExpectedClasses = false;
    while((expectedClass = va_arg(args, id)) != nil) {
        valInExpectedClasses = [val isKindOfClass:expectedClass];
        if (valInExpectedClasses) break;
    }
    
    va_end(args);
    */
    
    if (![val isKindOfClass:expectedClass]) {
        [NSException raise:@"InvalidValueException" format:@"expected value for key %@ to be of class %@, got %@", key, [expectedClass className], [val className]];
    }
    
    return val;
}

-(void) handleSendTextCommand:(NSDictionary*)data {
    
    NSString *chatIdentifier = [self safeJsonRead:data key:@"chatIdentifier" expectedClass:[NSString class]];
    NSString *text = [self safeJsonRead:data key:@"text" expectedClass:[NSString class]];
    
    NSString * _Nullable expressiveSendStyleID;
    NSObject *expressiveSendStyleFromJSON = data[@"expressiveSendStyleID"];
    if (expressiveSendStyleFromJSON == nil) {
        expressiveSendStyleID = nil;
    } else if ([expressiveSendStyleFromJSON isKindOfClass:[NSString class]]) {
        expressiveSendStyleID = (NSString*)expressiveSendStyleFromJSON;
    } else if (expressiveSendStyleFromJSON == [NSNull null]) {
        expressiveSendStyleID = nil;
    } else {
        [NSException raise:@"InvalidValueException" format:@"expected expressiveSendStyleID to be null or string, got value of class %@", [expressiveSendStyleFromJSON className]];
    }
    
    IMChatRegistry *registry = [IMChatRegistry sharedInstance];
    IMChat *chat = [registry existingChatWithChatIdentifier:chatIdentifier];
    
    [MessagesFunctionWrapper sendTextMessageToChat:chat textMessage:text expressiveSendStyleID:expressiveSendStyleID];
}

-(void) handleIncomingMessage:(id)message {
    NSData *messageData;
    if ([message isKindOfClass:[NSData class]]) {
        messageData = message;
    } else if ([message isKindOfClass:[NSString class]]) {
        NSString *messageStr = (NSString*) message;
        messageData = [messageStr dataUsingEncoding:NSUTF8StringEncoding];
    } else {
        [NSException raise:@"UnknownMessageClassException" format:@"cannot understand message of class %@", [message className]];
    }
    
    NSError *jsonErr = nil;
    id dict = [NSJSONSerialization JSONObjectWithData:messageData options:0 error:&jsonErr];
    if (jsonErr != nil) {
        [NSException raise:@"JSONSerializationException" format:@"failed to parse message: %@", jsonErr];
    }
    if (![dict isKindOfClass:[NSDictionary class]]) {
        //json array
        [NSException raise:@"InvalidJSONRootElementException" format:@"expected decoded JSON to be NSDictionary, got %@", [dict className]];
    }
    
    NSString *commandType = [self safeJsonRead:dict key:@"type" expectedClass:[NSString class]];
    NSDictionary *commandData = [self safeJsonRead:dict key:@"data" expectedClass:[NSDictionary class]];
    if ([commandType isEqualToString:@"sendText"]) {
        [self handleSendTextCommand:commandData];
    } else {
        [NSException raise:@"UnknownCommandTypeException" format:@"unknown command type %@", commandType];
    }
}

#pragma mark delegate

- (void)serverDidStart:(PSWebSocketServer *)server {
    INJLog(@"server started");
    
    NSNotificationCenter* notificationCenter = [NSNotificationCenter defaultCenter];
    [notificationCenter addObserver:self selector:@selector(imchatPropertiesChanged:) name:@"__kIMChatPropertiesChangedNotification" object:nil];
    [notificationCenter addObserver:self selector:@selector(imchatItemsDidChange:) name:@"__kIMChatItemsDidChangeNotification" object:nil];
}
- (void)serverDidStop:(PSWebSocketServer *)server {
    INJLog(@"server stopped");
}

- (BOOL)server:(PSWebSocketServer *)server acceptWebSocketWithRequest:(NSURLRequest *)request {
    INJLog(@"server should accept request %@", request);
    return YES;
}

- (void)server:(PSWebSocketServer *)server webSocketDidOpen:(PSWebSocket *)webSocket {
    INJLog(@"websocket %@ did open", webSocket);
    [self addWebSocket:webSocket];
}

- (void)server:(PSWebSocketServer *)server webSocket:(PSWebSocket *)webSocket didReceiveMessage:(id)message {
    INJLog(@"websocket %@ did receive message %@", webSocket, message);
    @try {
        [self handleIncomingMessage:message];
    } @catch (NSException *exception) {
        INJLog(@"exception handling incoming message %@: %@ - %@ %@", message, exception.name, exception.reason, [exception callStackSymbols]);
    }
}

- (void)server:(PSWebSocketServer *)server webSocket:(PSWebSocket *)webSocket didCloseWithCode:(NSInteger)code reason:(NSString *)reason wasClean:(BOOL)wasClean {
    INJLog(@"websocket %@ did close with code %@ reason %@ wasClean %@", webSocket, @(code), reason, @(wasClean));
    [self removeWebsocket:webSocket];
}

- (void)server:(PSWebSocketServer *)server webSocket:(PSWebSocket *)webSocket didFailWithError:(NSError *)error {
    INJLog(@"websocket %@ did fail with error %@", webSocket, error);
    [self removeWebsocket:webSocket];
}

- (void)server:(PSWebSocketServer *)server didFailWithError:(NSError *)error {
    INJLog(@"server did fail with error %@", error);
}


@end
