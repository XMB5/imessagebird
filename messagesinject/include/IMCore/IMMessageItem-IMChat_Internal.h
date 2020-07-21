//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <IMSharedUtilities/IMMessageItem.h>

@interface IMMessageItem (IMChat_Internal)
+ (Class)contextClass;
+ (id)displayNameForAddress:(id)arg1;
+ (BOOL)isLoginAddress:(id)arg1;
+ (id)handleForAddress:(id)arg1;
+ (id)bestAccountForAddress:(id)arg1;
- (id)_copyWithFlags:(unsigned long long)arg1;
- (id)_copy;
- (BOOL)_isInvitation;
- (void)_setInivtation:(BOOL)arg1;
- (id)message;
- (id)descriptionForPurpose:(long long)arg1 isGroupMessage:(BOOL)arg2 messageDataSource:(id)arg3 attachmentDataSource:(id)arg4;
- (id)descriptionForPurpose:(long long)arg1 isGroupMessage:(BOOL)arg2 senderDisplayName:(id)arg3 messageDataSource:(id)arg4 attachmentDataSource:(id)arg5;
- (BOOL)isIncomingTypingOrCancelTypingMessage;
- (BOOL)isTypingOrCancelTypingMessage;
- (BOOL)isCancelTypingMessage;
- (BOOL)isIncomingTypingMessage;
- (BOOL)isSystemMessage;
- (BOOL)isExtensibleMessageWithPluginPayload:(id *)arg1;
- (id)_service;
- (id)_newChatItemsWithFilteredChat:(BOOL)arg1 isBusiness:(BOOL)arg2 parentChatIsSpam:(BOOL)arg3 hasKnownParticipants:(BOOL)arg4;
- (id)_newChatItems;
- (BOOL)_hasMessageChatItem;
@end

