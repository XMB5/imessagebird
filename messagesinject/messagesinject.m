//
//  messagesinject.m
//  messagesinject
//
//  Created by Sam Foxman on 7/1/20.
//  Copyright © 2020 organization.name. All rights reserved.
//

#import "MessagesWebServer.h"
#import "MessagesFunctionWrapper.h"
#import "Logging.h"

#import <PSWebSocketServer.h>
#import <Foundation/Foundation.h>

#import <IMCore/IMAccountController.h>
#import <IMCore/IMAccount.h>
#import <IMCore/IMHandle.h>
#import <IMCore/IMChatRegistry.h>
#import <IMCore/IMChat.h>
#import <IMCore/IMMessage.h>
#import <IMCore/IMChatRegistry.h>
#import <IMCore/IMTranscriptPluginChatItem.h>
#import <IMCore/IMBalloonPluginDataSource.h>
#import <IMCore/IMBalloonPlugin.h>
#import <IMCore/IMChatItem.h>
#import <IMCore/IMPluginPayload.h>
#import <IMCore/IMParticipantChangeChatItem.h>
#import <IDS/IDSIDQueryController.h>

//extern void IMChatCalculateServiceForSendingNewComposeMaybeForce(id arg1, id arg2, id arg3, id arg4, id arg5, id arg6, id arg7, id arg8, id arg9, id arg10);
//extern id refreshServiceForSending(id arg1);

//useful resources
//https://github.com/GDSSecurity/OSX-Continuity-Dialer-POC/blob/master/SMShell/injectab.m
//https://github.com/Te-k/flexidie/tree/master/iOS/FlexiSPY%20Phoenix%204.9.6
//https://github.com/Chr0nicT/macOS-Headers-10.14.6-Mojave/tree/master/Applications/Messages/5500
//https://github.com/iosre/SMSNinja/blob/10ebe4c8c2ac1eaadb8c13d90730acae4278f30b/libsmsninja/libsmsninja-private.h
//https://web.archive.org/web/20200701002418/http://docshare04.docshare.tips/files/29808/298088226.pdf
//https://neosmart.net/blog/2018/imessage-for-windows/ (somewhat helpful, not much)

static PSWebSocketServer *server;
static MessagesWebServer *delegate;

static int DEFAULT_DELAY_BEFORE_START = 3;
static NSString* DEFAULT_HOST = @"127.0.0.1";
static NSUInteger DEFAULT_PORT = 1234;

@interface MessagesInject : NSObject

@end

@implementation MessagesInject

+(void) startServer {
    delegate = [MessagesWebServer new];
    NSDictionary *env = [[NSProcessInfo processInfo] environment];
    NSString *host = env[@"MESSAGESINJECT_SERVER_HOST"] ? : DEFAULT_HOST;
    NSUInteger port;
    NSString *portStr = env[@"MESSAGESINJECT_SERVER_PORT"];
    if (portStr) {
        port = [portStr integerValue] ? : DEFAULT_PORT;
    } else {
        port = DEFAULT_PORT;
    }
    INJLog(@"attempt to start server on host %@ port %@", host, @(port));
    server = [PSWebSocketServer serverWithHost:host port:port];
    server.delegate = delegate;
    [server start];
}

+(void) run {
    [self startServer];
    /*
    IMAccountController* accountController = [IMAccountController sharedInstance];
    IMAccount* account = [accountController activeIMessageAccount];
    INJLog(@"account login: %@  active: %d  connected: %d  canSendMessages: %d  isSMSRelayCapable: %d  allowsSMSRelay: %d  allowsMMSRelay: %d", [account login], (int) [account isActive], (int) [account isConnected], (int) [account canSendMessages], (int) [account isSMSRelayCapable], (int) [account allowsSMSRelay], (int) [account allowsMMSRelay]);
    */
    /*
    for (IMHandle* handle in [account arrayOfAllIMHandles]) {
        INJLog(@"handle %@ %@ %@ %@", [handle ID], [handle name], [handle displayID], [handle cnContact]);
    }
    */
    /*
    IMChatRegistry* registry = [IMChatRegistry sharedInstance];
    for (IMChat* chat in [registry allExistingChats]) {
        INJLog(@"chat %@", chat);
        for (IMChatItem* item in [chat chatItems]) {
            if ([item isKindOfClass:[IMParticipantChangeChatItem class]]) {
                IMParticipantChangeChatItem *participantChange = (IMParticipantChangeChatItem*)item;
                INJLog(@"part change changeType %lld sender %@ otherHandle %@", [participantChange changeType], [participantChange sender], [participantChange otherHandle]);
            }
        }
    }
    */
    //[self testFunc];
}

+(void) testFunc {
    /*
    INJLog(@"testFunc");
    IMAccountController* accountController = [IMAccountController sharedInstance];
    IMAccount* account = [accountController activeIMessageAccount];
    INJLog(@"active sms account found: %d", (int) ([accountController activeSMSAccount] != nil));
    INJLog(@"active imessage account found: %d", (int) ([accountController activeIMessageAccount] != nil));
    IMHandle* handle = [[IMHandle alloc] initWithAccount: account ID:@"+1MYPHONEHERE"];
    //NSOrderedSet *handles = [[NSOrderedSet alloc] initWithArray: @[ handle ]];
    //INJLog(@"handles %@", [handles array]);
    IMChatRegistry* registry = [IMChatRegistry sharedInstance];
    INJLog(@"registry %@", registry);
    IMChat *chat = [registry chatForIMHandle:handle];
    

    */
}

__attribute__((constructor)) static void loadMessagesInject() {
    NSString *delayBeforeStartStr = [[NSProcessInfo processInfo] environment][@"MESSAGESINJECT_DELAY_BEFORE_START"];
    int delayBeforeStart;
    if (delayBeforeStartStr) {
        delayBeforeStart = [delayBeforeStartStr intValue] ? : DEFAULT_DELAY_BEFORE_START;
    } else {
        delayBeforeStart = DEFAULT_DELAY_BEFORE_START;
    }
    INJLog(@"load messages inject");
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayBeforeStart * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        //not sure if autoreleasepool should be here?
        @autoreleasepool {
            @try {
                [MessagesInject run];
            } @catch(NSException *exception) {
                INJLog(@"fatal exception while running messages inject: %@ - %@ %@", exception.name, exception.reason, [exception callStackSymbols]);
                exit(1);
            }
        }
    });
}

@end
