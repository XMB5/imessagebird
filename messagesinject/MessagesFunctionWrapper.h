//
//  MessagesFunctionWrapper.h
//  messagesinject
//
//  Created by Sam Foxman on 7/3/20.
//  Copyright © 2020 organization.name. All rights reserved.
//

#ifndef MESSAGESINJECT_FUNCTION_WRAPPER_HEADER_IMPORTED
#define MESSAGESINJECT_FUNCTION_WRAPPER_HEADER_IMPORTED

#import <Foundation/Foundation.h>
#import <IMCore/IMChat.h>

NS_ASSUME_NONNULL_BEGIN

//not official Apple constants -- these were reversed engineered from IMCore and Messages
//probably #define'd in some private IMCore header
enum {
    kIMMessageIsFinished = 1, //instantMessageForInputLineString:baseWritingDirection:flags:
    kIMMessageIsSystemMessage = 1 << 0xe //isSystemMessage
};
//kIMMessageIsTypingIndicator = 0x100000; //not sure about this one
//some other flags indicate whether the message is a typing indicator or typing cancel message


//typing indicator
//-[IMChat setLocalUserIsTyping:true];
//equivalent to [chat setLocalUserIsComposing:@"__kIMChatComposeTyping"]
//lasts for 1 minute
//to turn off:
//-[IMChat setLocalUserIsTyping:true];
//takes 3 seconds before something actually sends the message to turn off the typing indicator
//typing indicator with image
/*
 //image should be accessible from Messages.app (ldid -e /.../Messages)
 //~/Desktop or ~/Library/Messages
NSData *iconData = [NSData dataWithContentsOfFile:@"/Users/USER/Desktop/image.jpg"];
if (iconData == nil || iconData.length == 0) {
    INJLog(@"no icon data");
    abort();
}
IMMessage* message = [[IMMessage alloc] initWithSender:nil fileTransfer:nil];
message.messageSummaryInfo = @{
    @"ust": @YES
};
message.flags = 1008;
message.customTypingIndicatorIcon = iconData;
NSString *prefix = @"com.apple.messages.MSMessageExtensionBalloonPlugin:AAAAAAAAAA:com.unrecognized.bundle.id.9c911118b42cf9ca670aca3d7f794554.";
NSMutableString *bundleId = [prefix mutableCopy];
//add new randomness each time to prevent any caching (I don't think there is any icon data caching but I'm not sure)
for (int i = 0; i < 16; i++) {
    [bundleId appendFormat:@"%02x", arc4random() % 256];
}
message.balloonBundleID = bundleId;
INJLog(@"msg %@", message);
[chat _sendMessage:message adjustingSender:1 shouldQueue:0];
*/

//load more messages
//[chat setNumberOfMessagesToKeepLoaded:0 limit:70];
//[chat loadMessagesBeforeDate:0 limit:70];
//does not happen infstnatly, will be emitted through NSNotificationCenter when loaded
//limit is total number of messages (counted by [chat messagesCount]) to have in chat after loading
//[chat messagesCount] != [[chat chatItems] count] although they are similar
//reversed from [ChatController _performQueryForAdditionalItems:isInitialLoad:] in Messages

@interface MessagesFunctionWrapper : NSObject

/**
Wrapper around [IDSIDQueryController forceRefreshIDStatusForDestinations].
Normally, forceRefresh is only called if using iMessages and lastSentMessage was not delivered (isDelivered property)
See recipientHandlesDidChange in SocialUI.framework

@discussion
calllback maps mailto:<address> or tel:<address> to either
0==Error? (not sure about this)
1==SMS/not iMessage
2==iMessage

@param destinations addresses to get statuses for, with the protocol or without (it seems like the protocol does not matter at all), ex: @"8001231231" or @"mailto:email@icloud.com"

*/
+(void) forceRefreshStatusForDestinations:(NSArray*) destinations queue:(dispatch_queue_t)queue callback:(void(^)(NSDictionary* statuses))callback;

/**
 Wrapper around [IDSIDQueryController refreshIDStatusForDestinations].
 @see forceRefreshStatusForDestinations
 */
+(void) refreshStatusForDestinations:(NSArray*) destinations queue:(dispatch_queue_t)queue callback:(void(^)(NSDictionary* statuses))callback;

/**
 Wrapper around [IDSIDQueryController _currentIDStatusForDestinations].
 Why _currentIdStatusForDestinations instead of currentIdStatusForDestinations? Because that is what IMCore.framework does in IMChatCalculateServiceForSendingNewComposeMaybeForce
 @see forceRefreshStatusForDestinations
 */
+(NSDictionary*) cachedStatusForDestinations:(NSArray*) destinations;

/**
 Wrapper around
 [IMChat setNumberOfMessagesToKeepLoaded:];
 [IMChat loadMessagesBeforeDate:limit:];
 Does not load more messages instantly after returning
 Instead, monitor imchatPropertiesChanged:/imchatItemsChanged: on NSNotificationCenter
 */
+(void) loadMoreMessagesInChat:(IMChat*)chat numMoreMessages:(unsigned long long)numMoreMessages;

/**
 Wrapper around
 [IMMessage instantMessageWithText:messageSubject:flags:expressiveSendStyleID:]
 [IMChat sendMessage:]
 @param expressiveSendStyleID Message effect, for example balloons or fireworks
    See list at url below (link may be to old version of iMessageParity) https://github.com/LumingYin/iMessageParity/blob/edc85ed237bb3f43c75faa13f46becc14190801e/iMessageParity/iMessageParity.m#L28 also, "Screen" effects are located at /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Library/Developer/CoreSimulator/Profiles/Runtimes/iOS.simruntime/Contents/Resources/RuntimeRoot/System/Library/Messages/iMessageEffects/
 */
+(void) sendTextMessageToChat:(IMChat*)chat textMessage:(NSString*)textMessage expressiveSendStyleID:(NSString* _Nullable)expressiveSendStyleID;

@end

NS_ASSUME_NONNULL_END

#endif
