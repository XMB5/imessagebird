//
//  MessagesFunctionWrapper.m
//  messagesinject
//
//  Created by Sam Foxman on 7/3/20.
//  Copyright © 2020 organization.name. All rights reserved.
//

#import "MessagesFunctionWrapper.h"

#import <IDS/IDSIDQueryController.h>
#import <IMCore/IMMessage.h>

static NSString* idQueryControllerService = @"com.apple.madrid";
static NSString* idQueryControllerListenerID = @"__kIMChatServiceForSendingIDSQueryControllerListenerID";

@implementation MessagesFunctionWrapper

+(void) forceRefreshStatusForDestinations:(NSArray*) destinations queue:(dispatch_queue_t)queue callback:(void(^)(NSDictionary* statuses))callback {
    
    IDSIDQueryController* idQueryController = [IDSIDQueryController sharedInstance];
    [idQueryController forceRefreshIDStatusForDestinations:destinations service:idQueryControllerService listenerID:idQueryControllerListenerID queue:queue completionBlock:callback];
    
}

+(void) refreshStatusForDestinations:(NSArray*) destinations queue:(dispatch_queue_t)queue callback:(void(^)(NSDictionary* statuses))callback {
    
    IDSIDQueryController* idQueryController = [IDSIDQueryController sharedInstance];
    [idQueryController refreshIDStatusForDestinations:destinations service:idQueryControllerService listenerID:idQueryControllerListenerID queue:queue completionBlock:callback];
}

+(NSDictionary*) cachedStatusForDestinations:(NSArray*) destinations {
    
    IDSIDQueryController* idQueryController = [IDSIDQueryController sharedInstance];
    return [idQueryController _currentIDStatusForDestinations:destinations service:idQueryControllerService listenerID:idQueryControllerListenerID];
}

+(void) loadMoreMessagesInChat:(IMChat*)chat numMoreMessages:(unsigned long long)numMoreMessages {
    unsigned long long limit = [chat messageCount] + numMoreMessages;
    [chat setNumberOfMessagesToKeepLoaded:limit];
    [chat loadMessagesBeforeDate:0 limit:limit];
}

+(void) sendTextMessageToChat:(IMChat*)chat textMessage:(NSString*)textMessage expressiveSendStyleID:(NSString* _Nullable)expressiveSendStyleID {
    NSAttributedString *attribtuedText = [[NSAttributedString alloc] initWithString:textMessage];
    
    //sendInChatScriptCommand: in Messages uses 1 for flags, not sure what it means but it works
    IMMessage *message = [IMMessage instantMessageWithText:attribtuedText messageSubject:nil flags:1 expressiveSendStyleID:expressiveSendStyleID];
    [chat sendMessage:message];
}

/*
 
//this works but has multiple callbacks
//designed to change color of token when typing in recipient field
//not useful for remote iMessages
//also it seems like I'm missing some important parameter so it crashes sometimes
NSMutableSet* set = [NSMutableSet setWithObject:@"tel:+18001234567"];
IMChatCalculateServiceForSendingNewComposeMaybeForce([set allObjects], nil, nil, nil, nil, nil, nil, nil, nil, ^(id arg1, id arg2){
    //arg1 has contact's photo?
    NSLog(@"callback arg2 %@", arg2);
});

 */


@end
