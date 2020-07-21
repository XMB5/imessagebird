//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <objc/NSObject.h>

@class DDScannerResult, IMChat, IMMessage, IMPluginPayload, LPLinkMetadata, NSArray, NSAttributedString, NSData, NSMutableSet, NSString, NSURL;

//subclasses in /System/Library/Messages/iMessageBalloons/RichLinkProvider.bundle/Contents/MacOS/RichLinkProvider

@interface IMBalloonPluginDataSource : NSObject
{
    BOOL _payloadInShelf;
    BOOL _initialMessageIsFromMe;
    BOOL _isLast;
    BOOL _isShowingLatestMessageAsBreadcrumb;
    BOOL _hasInvalidatedSize;
    BOOL _parentChatHasAllUnknownRecipients;
    BOOL _showingLatestMessageAsBreadcrumb;
    IMChat *_chat;
    IMPluginPayload *_pluginPayload;
    NSURL *_url;
    DDScannerResult *_dataDetectedResult;
    NSArray *_attachmentGUIDs;
    NSURL *_URLToOpenOnTapAction;
    NSArray *_pendingAttachmentData;
    NSMutableSet *_temporaryAttachmentURLs;
    NSString *__imMessageGUID;
    NSString *_messageGUID;
    NSString *_sessionGUID;
    NSString *_bundleID;
    NSArray *_consumedPayloads;
    NSString *_guidOfLastMessageInSession;
    long long _messageIDOfLastMessageInSession;
}

+ (id)replaceHandleWithContactNameInString:(id)arg1 forAccount:(id)arg2 additionalHandles:(id)arg3;
+ (BOOL)supportsIndividualPreviewSummaries;
+ (id)individualPreviewSummaryForPluginPayload:(id)arg1;
+ (id)previewSummary;
+ (id)previewSummaryForPluginPayload:(id)arg1 withBundleID:(id)arg2 previewAttachmentURL:(id *)arg3 previewAttachmentUTI:(id *)arg4;
+ (id)previewSummaryForPluginBundle:(id)arg1;
+ (id)unlocalizedPreviewSummaryForPluginBundle:(id)arg1 pluginDisplayName:(id)arg2;
+ (BOOL)supportsURL:(id)arg1;
//- (void).cxx_destruct;
@property(readonly, nonatomic) long long messageIDOfLastMessageInSession; // @synthesize messageIDOfLastMessageInSession=_messageIDOfLastMessageInSession;
@property(readonly, retain, nonatomic) NSString *guidOfLastMessageInSession; // @synthesize guidOfLastMessageInSession=_guidOfLastMessageInSession;
@property(readonly, nonatomic, getter=isShowingLatestMessageAsBreadcrumb) BOOL showingLatestMessageAsBreadcrumb; // @synthesize showingLatestMessageAsBreadcrumb=_showingLatestMessageAsBreadcrumb;
@property(nonatomic) BOOL parentChatHasAllUnknownRecipients; // @synthesize parentChatHasAllUnknownRecipients=_parentChatHasAllUnknownRecipients;
@property(retain, nonatomic) NSArray *consumedPayloads; // @synthesize consumedPayloads=_consumedPayloads;
@property(nonatomic) BOOL hasInvalidatedSize; // @synthesize hasInvalidatedSize=_hasInvalidatedSize;
@property(readonly, retain, nonatomic) NSString *bundleID; // @synthesize bundleID=_bundleID;
@property(retain, nonatomic) NSString *sessionGUID; // @synthesize sessionGUID=_sessionGUID;
@property(retain, nonatomic) NSString *messageGUID; // @synthesize messageGUID=_messageGUID;
@property(nonatomic, setter=setShowingLatestMessageAsBreadcrumb:) BOOL isShowingLatestMessageAsBreadcrumb; // @synthesize isShowingLatestMessageAsBreadcrumb=_isShowingLatestMessageAsBreadcrumb;
@property(retain, nonatomic) NSString *_imMessageGUID; // @synthesize _imMessageGUID=__imMessageGUID;
@property(retain, nonatomic) NSMutableSet *temporaryAttachmentURLs; // @synthesize temporaryAttachmentURLs=_temporaryAttachmentURLs;
@property(retain, nonatomic) NSArray *pendingAttachmentData; // @synthesize pendingAttachmentData=_pendingAttachmentData;
@property(nonatomic, setter=setLast:) BOOL isLast; // @synthesize isLast=_isLast;
@property(nonatomic) BOOL initialMessageIsFromMe; // @synthesize initialMessageIsFromMe=_initialMessageIsFromMe;
@property(readonly, nonatomic) NSURL *URLToOpenOnTapAction; // @synthesize URLToOpenOnTapAction=_URLToOpenOnTapAction;
@property(retain, nonatomic) NSArray *attachmentGUIDs; // @synthesize attachmentGUIDs=_attachmentGUIDs;
@property(retain, nonatomic) DDScannerResult *dataDetectedResult; // @synthesize dataDetectedResult=_dataDetectedResult;
@property(retain, nonatomic) NSURL *url; // @synthesize url=_url;
@property(nonatomic) BOOL payloadInShelf; // @synthesize payloadInShelf=_payloadInShelf;
@property(retain, nonatomic) IMPluginPayload *pluginPayload; // @synthesize pluginPayload=_pluginPayload;
@property(retain, nonatomic) IMChat *chat; // @synthesize chat=_chat;
- (id)description;
- (void)_reloadLatestUnconsumedBreadcrumb;
- (void)endShowingLastConsumedBreadcrumb;
- (void)beginShowingLastConsumedBreadcrumbForOutgoingPayload:(id)arg1;
- (id)_replaceHandleWithContactNameInString:(id)arg1;
@property(readonly, nonatomic) LPLinkMetadata *richLinkMetadata;
- (void)datasourceWasMovedToNewGuid:(id)arg1;
- (struct CGSize)sizeThatFits:(struct CGSize)arg1;
- (id)individualPreviewAttachmentFileAndUTI:(id *)arg1;
- (id)_summaryText;
- (id)individualPreviewSummary;
- (void)stopPlayback;
- (void)playbackWithCompletionBlock:(id)arg1;
- (unsigned long long)playbackType;
- (void)markAsPlayed;
- (void)needsResize;
@property(readonly, nonatomic) BOOL supportsDynamicSize;
- (void)statusStringNeedsUpdate;
@property(readonly, nonatomic) BOOL wantsReplyFromContentView;
- (void)didTapStatusItem;
@property(readonly, retain, nonatomic) NSAttributedString *statusAttributedString;
@property(readonly, retain, nonatomic) NSString *statusString;
@property(readonly, nonatomic) BOOL wantsStatusItem;
- (void)payloadWillSendFromShelf;
- (void)payloadWillEnterShelf;
- (void)thumbnailURLWithSize:(struct CGSize)arg1 completion:(id)arg2;
- (void)payloadDidChange;
- (void)pluginPayloadDidChange:(unsigned long long)arg1;
@property(readonly, nonatomic) BOOL isPlayed;
@property(readonly, nonatomic) BOOL isFromMe;
- (unsigned long long)_updateWithPluginPayload:(id)arg1 messageID:(long long)arg2 messageGUID:(id)arg3;
- (void)_removeTemporaryAttachmentURLs;
- (void)_updateTemporaryAttachmentURLsForPluginPayload;
- (BOOL)_senderIsSameBetweenPayload:(id)arg1 andOtherPayload:(id)arg2;
- (void)_updatePayload:(id)arg1 messageID:(long long)arg2 messageGUID:(id)arg3;
- (void)updatePayload:(id)arg1 attachments:(id)arg2;
- (void)updatePayload:(id)arg1;
- (void)sendPayload:(id)arg1 attachments:(id)arg2;
- (void)sendPayload:(id)arg1;
@property(readonly, nonatomic) IMMessage *imMessage;
@property(readonly, retain, nonatomic) NSData *messagePayloadDataForSending;
- (void)setPayload:(id)arg1 attachments:(id)arg2;
@property(retain, nonatomic) NSData *payload;
//payload is encoded with NSKeyedArchiver
//refer to https://developer.apple.com/documentation/businesschatapi/messages_sent/sending_rich_link_messages
//and https://developer.apple.com/documentation/businesschatapi/messages_sent/interactive_messages/sending_interactive_messages
//for understanding contents of keyed archive
@property(readonly, nonatomic) NSArray *allPayloads;
- (id)initWithPluginPayload:(id)arg1;
- (id)initWithMessageGUID:(id)arg1 payload:(id)arg2 dataDetectedResult:(id)arg3 url:(id)arg4;

@end

