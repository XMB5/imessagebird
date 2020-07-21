//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <objc/NSObject.h>

@class NSMutableDictionary;

@interface IMCommLimitsPolicyCache : NSObject
{
    NSMutableDictionary *_conversationContextToParticipantIDsHash;
    NSMutableDictionary *_participantIDsHashToConversationContext;
    NSMutableDictionary *_participantIDsHashToChatIdentifier;
    NSMutableDictionary *_chatIdentifierToParticipantIDsHash;
}

//- (void).cxx_destruct;
@property(retain, nonatomic) NSMutableDictionary *chatIdentifierToParticipantIDsHash; // @synthesize chatIdentifierToParticipantIDsHash=_chatIdentifierToParticipantIDsHash;
@property(retain, nonatomic) NSMutableDictionary *participantIDsHashToChatIdentifier; // @synthesize participantIDsHashToChatIdentifier=_participantIDsHashToChatIdentifier;
@property(retain, nonatomic) NSMutableDictionary *participantIDsHashToConversationContext; // @synthesize participantIDsHashToConversationContext=_participantIDsHashToConversationContext;
@property(retain, nonatomic) NSMutableDictionary *conversationContextToParticipantIDsHash; // @synthesize conversationContextToParticipantIDsHash=_conversationContextToParticipantIDsHash;
- (id)contextForParticipantIDsHash:(id)arg1;
- (void)addSentinelContextForParticipantIDsHash:(id)arg1;
- (void)addTrackingForConversationContext:(id)arg1 forParticipantIDsHash:(id)arg2;
- (id)conversationContextForChat:(id)arg1;
- (id)chatForConversationContext:(id)arg1;
- (id)chatForParticipantIDsHash:(id)arg1;
- (BOOL)isFetchingCommLimitsPolicyForChat:(id)arg1;
- (void)removeTrackingForChat:(id)arg1;
- (void)addTrackingForChat:(id)arg1;
- (id)init;

@end

