//
//  ChatItemSerializer.m
//  messagesinject
//
//  Created by Sam Foxman on 7/19/20.
//  Copyright © 2020 organization.name. All rights reserved.
//

#import "Serializer.h"

#import <IMCore/IMHandle.h>
#import <IMCore/IMTranscriptChatItem.h>
#import <IMCore/IMMessagePartChatItem.h>
#import <IMCore/IMSenderChatItem.h>
#import <IMCore/IMDateChatItem.h>
#import <IMCore/IMServiceChatItem.h>
#import <IMCore/IMMessageStatusChatItem.h>
#import <IMCore/IMAttachmentMessagePartChatItem.h>
#import <IMCore/IMAudioMessageChatItem.h>
#import <IMCore/IMLoadMoreChatItem.h>
#import <IMCore/IMTranscriptPluginChatItem.h>
#import <IMCore/IMBalloonPluginDataSource.h>
#import <IMCore/IMGroupActionChatItem.h>
#import <IMCore/IMGroupTitleChangeChatItem.h>
#import <IMCore/IMParticipantChangeChatItem.h>
#import <IMCore/IMTextMessagePartChatItem.h>
#import <IMCore/IMTypingChatItem.h>
#import <IMCore/IMTypingPluginChatItem.h>
#import <IMCore/IMChat.h>

#import <Contacts/Contacts.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
//we need to use IMServiceImpl to determine the name of the service in IMServiceChatItem
//however, IMServiceImpl inherits from IMService from InstatMessage.framework (/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/InstantMessage.framework/Headers)
//and IMService is deprecated
//come on apple, using deprecated classes!
#import <IMCore/IMServiceImpl.h>
#pragma clang diagnostic pop

@implementation Serializer

+ (NSString*) stringify:(NSDictionary*)dict {
    NSError *jsonErr = nil;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:dict options:0 error:&jsonErr];
    if (jsonErr != nil) {
        [NSException raise:@"JSONSerializationException" format:@"failed to serialize dictionary %@: %@", dict, jsonErr];
    }
    return [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
}

+ (id) jsonSafeNullable:(id)obj {
    return obj == nil ? [NSNull null] : obj;
}

+ (id) dictForIMHandle:(IMHandle*)handle {
    if (handle == nil) {
        return [NSNull null];
    } else {
        CNContact *cnContact = [handle cnContact]; //CNContact if found in address book, CNMutableContact if not in address book
        id contactIdentifier = ([cnContact isMemberOfClass: [CNMutableContact class]]) ? [NSNull null] : [cnContact identifier];
        return @{
            @"id": [handle ID],
            @"contactIdentifier": contactIdentifier
        };
    }
}

+ (NSDictionary*) dictForIMTextMessagePartChatItem:(IMTextMessagePartChatItem*)item {
    NSMutableArray *attrList = [NSMutableArray new];
    NSAttributedString *text = [item text];
    id textString;
    
    if (text == nil) {
        textString = [NSNull null];
    } else {
        textString = [text string];
        [text enumerateAttributesInRange:NSMakeRange(0, text.length) options:0 usingBlock:^(NSDictionary<NSAttributedStringKey,id> * _Nonnull attrs, NSRange range, BOOL * _Nonnull stop) {
            
            NSURL *href = [attrs valueForKey:@"__kIMLinkAttributeName"];
            if (href != nil) {
                [attrList addObject:@{
                    @"type": @"href", //let frontend extract href using location and length, more secure
                    @"location": @(range.location),
                    @"length": @(range.length)
                }];
            }
            //there are probably more attributes
            //there seems to be an attribtue that allows 1 text message to be split up into multiple IMTextMessagePartChatItems but I have not seen it used
        }];
    }
    
    return @{
        @"isFromMe": @((bool)[item isFromMe]),
        @"string": textString,
        @"attrList": attrList
    };
}

+ (NSDictionary*) dictForIMSenderChatItem:(IMSenderChatItem*)item {
    NSDictionary *handleData = [self dictForIMHandle:[item handle]];
    return @{
        @"handle": handleData
    };
}

+ (NSDictionary*) dictForIMDateChatItem:(IMDateChatItem*)item {
    NSTimeInterval secondsSince1970 = [[item date] timeIntervalSince1970];
    return @{
        @"secondsSince1970": @(secondsSince1970)
    };
}

+ (NSDictionary*) dictForIMServiceChatItem:(IMServiceChatItem*)item {
    IMServiceImpl *service = [item service];
    id serviceNameForJSON = service == nil ? [NSNull null] : [service name];
    
    return @{
        //if both are null, ignore the message (not sure why this happens, may be associated with group title change)
        @"serviceName": serviceNameForJSON, //"iMessage" or "SMS", never localized
        @"handle": [self dictForIMHandle:[item handle]] //ex "iMessage with +1 (800) 123-1231" (not name, even though in contacts)
    };
}

+ (NSDictionary*) dictForIMMessageStatusItem:(IMMessageStatusChatItem*)item {
    return @{
        @"isFromMe": @((bool)[item isFromMe]),
        @"statusType": @([item statusType]),
        @"expireStatusType": @([item expireStatusType])
    };
}

+ (NSDictionary*) dictForIMAttachmentMessagePartChatItem:(IMAttachmentMessagePartChatItem*)item {
    return @{
        @"isFromMe": @((bool)[item isFromMe]),
        @"transferGUID": [item transferGUID]
    };
}

+ (NSDictionary*) dictForIMAudioMessageChatItem:(IMAudioMessageChatItem*)item {
    return @{
        @"isSaved": @((BOOL) [item isSaved]),
        @"isPlayed": @((BOOL)[item isPlayed]),
        @"attachmentMessagePartData": [self dictForIMAttachmentMessagePartChatItem:item]
    };
}

+ (NSDictionary*) dictForIMLoadMoreChatItem:(IMLoadMoreChatItem*)item {
    return @{}; //nothing to display to the user -- when this item is reached, request to load more messages
}

+ (NSDictionary*) dictForIMTranscriptPluginChatItem:(IMTranscriptPluginChatItem*)item {
    //this message item covers rich links, handwriting, digital touch, and some other iMessage extensions like GamePigeon
    IMBalloonPluginDataSource *dataSource = [item dataSource];
    NSString *balloonBundleID = [item balloonBundleID];
    if ([balloonBundleID isEqualToString:@"com.apple.messages.URLBalloonProvider"]) {
        //rich link
        //doc at https://developer.apple.com/documentation/businesschatapi/messages_sent/sending_rich_link_messages
        
        NSURL *originalURL;
        NSURL *redirectedURL;
        NSString *title;
        NSString *summary;

        //could not import LinkPresentation for some reason, so using a dynamic workaround
        //also this way we get to use the undocument summary property
        //there are some other undocumented properties too, decompile LinkPresentation to see them
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wundeclared-selector"
        NSObject *lpLinkMetadata = (NSObject*) [dataSource richLinkMetadata];
        if (lpLinkMetadata) {
            if ([lpLinkMetadata respondsToSelector:@selector(originalURL)]) {
                originalURL = [lpLinkMetadata performSelector:@selector(originalURL)];
            }
            if ([lpLinkMetadata respondsToSelector:@selector(URL)]) {
                //yes, URL is capitalized -- you are looking at the swift docs, not the objective-c docs
                redirectedURL = [lpLinkMetadata performSelector:@selector(URL)];
            }
            if ([lpLinkMetadata respondsToSelector:@selector(summary)]) {
                summary = [lpLinkMetadata performSelector:@selector(summary)];
            }
            if ([lpLinkMetadata respondsToSelector:@selector(title)]) {
                title = [lpLinkMetadata performSelector:@selector(title)];
            }
        }
#pragma clang diagnostic pop
        
        if (originalURL == nil) {
            originalURL = [dataSource url];
        }
        
        id originalURLforJSON = originalURL == nil ? [NSNull null] : [originalURL absoluteString];
        id redirectedURLforJSON = redirectedURL == nil ? [NSNull null] : [redirectedURL absoluteString];
        
        return @{
            @"type": @"url",
            @"originalURL": originalURLforJSON,
            @"redirectedURL": redirectedURLforJSON,
            @"title": [self jsonSafeNullable:title],
            @"summary": [self jsonSafeNullable:summary]
        };
    } else {
        //if you decode [dataSource payload] with NSKeyedUnarchiver you get some more data
        id summaryText = [self jsonSafeNullable:[dataSource _summaryText]]; //decodes payload and returns the field "ldtext" which stands for LocalizedDescriptionText
        return @{
            @"type": @"unknown",
            @"balloonBundleID": balloonBundleID, //examples: com.apple.DigitalTouchBalloonProvider, com.apple.Handwriting.HandwritingProvider, com.apple.messages.MSMessageExtensionBalloonPlugin:EWFNLB79LQ:com.gamerdelights.gamepigeon.ext
            @"summaryText": summaryText
        };
    }
}

+ (NSDictionary*) dictForIMGroupActionChatItem:(IMGroupActionChatItem*)item {
    //[ChatItemDOMProvider _parseGroupActionChatItem:]
    return @{
        @"actionType": @([item actionType]), //see comment in IMGroupActionChatItem.h
        @"sender": [self dictForIMHandle:[item sender]]
    };
}

+ (NSDictionary*) dictForIMGroupTitleChangeChatItem:(IMGroupTitleChangeChatItem*)item {
    return @{
        @"title": [self jsonSafeNullable:[item title]], //if title==nil, then the title was removed
        @"sender": [self dictForIMHandle:[item sender]] //if sender==nil, then the end user changed the title (displayed as "You named the conversation <title>")
    };
}

+ (NSDictionary*) dictForIMParticipantChangeChatItem:(IMParticipantChangeChatItem*)item {
    id serviceNameForJSON; // = [[[item otherHandle] service] name]
    
    IMHandle *otherHandle = [item otherHandle];
    if (otherHandle != nil) {
        IMServiceImpl *service = [otherHandle service];
        if (service != nil) {
            serviceNameForJSON = [service name];
        } else {
            serviceNameForJSON = [NSNull null];
        }
    } else {
        serviceNameForJSON = [NSNull null];
    }
    
    return @{
        @"changeType": @([item changeType]),
        @"sender": [self dictForIMHandle:[item sender]],
        @"otherHandle": [self dictForIMHandle:[item otherHandle]],
        @"serviceName": serviceNameForJSON
    };
}

+ (NSDictionary*) dictForIMTypingChatItem:(IMTypingChatItem*)item {
    return @{}; //has no data
}

+ (NSDictionary*) dictForIMTypingPluginChatItem:(IMTypingPluginChatItem*)item {
    return @{}; //has dataSource and typingIndicatorIcon, will maybe implement in future (although it is a lot of work for a minor feature)
    //typingIndicatorIcon is jpeg data
}

+ (NSDictionary*) dictForIMChatItem:(IMChatItem*)item {
    //see [ChatItemDOMProvider parseChatItem:chat:] and related functions in SocialUI
    //also look at headers matching <IMCore/IM*ChatItem.h>
    
    NSString *type;
    NSDictionary *data;
    if ([item isMemberOfClass:[IMTextMessagePartChatItem class]]) {
        type = @"textMessagePart";
        data = [self dictForIMTextMessagePartChatItem:(IMTextMessagePartChatItem*)item];
    } else if ([item isMemberOfClass:[IMSenderChatItem class]]) {
        type = @"sender";
        data = [self dictForIMSenderChatItem:(IMSenderChatItem*)item];
    } else if ([item isMemberOfClass:[IMDateChatItem class]]) {
        type = @"date";
        data = [self dictForIMDateChatItem:(IMDateChatItem*)item];
    } else if ([item isMemberOfClass:[IMServiceChatItem class]]) {
        type = @"service";
        data = [self dictForIMServiceChatItem:(IMServiceChatItem*)item];
    } else if ([item isMemberOfClass:[IMAttachmentMessagePartChatItem class]]) {
        type = @"attachmentMessagePart";
        data = [self dictForIMAttachmentMessagePartChatItem:(IMAttachmentMessagePartChatItem*)item];
    } else if ([item isMemberOfClass:[IMAudioMessageChatItem class]]) {
        type = @"audioMessage";
        data = [self dictForIMAudioMessageChatItem:(IMAudioMessageChatItem*)item];
    } else if ([item isMemberOfClass:[IMLoadMoreChatItem class]]) {
        type = @"loadMore";
        data = [self dictForIMLoadMoreChatItem:(IMLoadMoreChatItem*)item];
    } else if ([item isMemberOfClass:[IMTranscriptPluginChatItem class]]) {
        type = @"transcriptPlugin";
        data = [self dictForIMTranscriptPluginChatItem:(IMTranscriptPluginChatItem*)item];
    } else if ([item isMemberOfClass:[IMMessageStatusChatItem class]]) {
        type = @"messageStatus";
        data = [self dictForIMMessageStatusItem:(IMMessageStatusChatItem*)item];
    } else if ([item isMemberOfClass:[IMGroupActionChatItem class]]) {
        type = @"groupAction";
        data = [self dictForIMGroupActionChatItem:(IMGroupActionChatItem*)item];
    } else if ([item isMemberOfClass:[IMGroupTitleChangeChatItem class]]) {
        type = @"groupTitleChange";
        data = [self dictForIMGroupTitleChangeChatItem:(IMGroupTitleChangeChatItem*)item];
    } else if ([item isMemberOfClass:[IMParticipantChangeChatItem class]]) {
        type = @"participantChange";
        data = [self dictForIMParticipantChangeChatItem:(IMParticipantChangeChatItem*)item];
    } else if ([item isMemberOfClass:[IMTypingChatItem class]]) {
        type = @"typing";
        data = [self dictForIMTypingChatItem:(IMTypingChatItem*)item];
    } else if ([item isMemberOfClass:[IMTypingPluginChatItem class]]) {
        type = @"typingPlugin";
        //when other user is about to send animoji or sticker
        //on macos it appears to display the same as IMTypingChatItem
        //except on iOS is apparently shows [item typingIndicatorIcon]
        //https://www.howtogeek.com/332300/do-imessages-typing-bubbles-only-appear-when-im-actively-typing/
        data = [self dictForIMTypingPluginChatItem:(IMTypingPluginChatItem*)item];
    } else {
        type = @"unknown";
        //there are lots more types
        data = @{
            @"className": [item className]
        };
    }
    
    id guid;
    if ([item isKindOfClass:[IMTranscriptChatItem class]]) {
        //it seems like all chat items are subclasses of IMTranscriptChatItem
        //but just to be safe I'll leave this check in here
        IMTranscriptChatItem *transcriptChatItem = (IMTranscriptChatItem*)item;
        guid = [transcriptChatItem guid];
    } else {
        guid = [NSNull null];
    }
    
    return @{
        @"type": type,
        @"guid": guid,
        @"data": data
    };
}

+ (NSDictionary*) dictForIMChat:(IMChat*)chat {
    NSMutableArray *chatItems = [NSMutableArray new];
    for (IMChatItem* item in [chat chatItems]) {
        [chatItems addObject:[Serializer dictForIMChatItem:item]];
    }
    
    NSMutableArray *participants = [NSMutableArray new];
    for (IMHandle *participant in [chat participants]) {
        [participants addObject:[Serializer dictForIMHandle:participant]];
    }
    
    id displayName = [Serializer jsonSafeNullable:[chat displayName]];
    return @{
        @"chatIdentifier": [chat chatIdentifier],
        @"displayName": displayName,
        @"unreadMessageCount": @([chat unreadMessageCount]),
        @"participants": participants,
        @"chatItems": chatItems
    };
}

+ (NSDictionary*) dictForIMChatItemsDidChangeNotification:(NSNotification*)notification {
    //ref: [IMChat _updateChatItemsWithReason:block:shouldPost:] and [IMChat _postIMChatItemsDidChangeNotificationWithInserted:removed:reload:regenerate:oldChatItems:shouldLog:] in IMCore
    IMChat *chat = [notification object];
    NSDictionary* userInfo = [notification userInfo];
    //it appears that these NSIndexSets are generated based on oldItems and [chat chatItems] (the new items)
    
    NSIndexSet *reloadItems = [userInfo valueForKey:@"__kIMChatItemsReload"];
    //indices of [chat chatItems]
    //[IMTranscriptChatItemRules _shouldReloadChatItem:oldChatItem:] in IMCore
    //whenever some property of the IMChatItem changes (for example isPlayed or contiguousType)
    
    //NSIndexSet *regenerateItems = [userInfo valueForKey:@"__kIMChatItemsRegenerate"];
    //indices of [chat chatItems]
    //when a ChatItem is replaced by a ChatItem in a different location in ram?
    
    NSIndexSet *removedItems = [userInfo valueForKey:@"__kIMChatItemsRemoved"]; //indices of oldItems
    NSIndexSet *insertedItems = [userInfo valueForKey:@"__kIMChatItemsInserted"]; //indices of [chat chatItems]
    //NSArray *oldItems = [userInfo valueForKey:@"__kIMChatItemsOldItems"];
    
    NSMutableArray *removedForJSON = [NSMutableArray new];
    [removedItems enumerateRangesUsingBlock:^(NSRange range, BOOL * _Nonnull stop) {
        NSDictionary *rangeDict = @{
            @"location": @(range.location),
            @"length": @(range.length)
        };
        [removedForJSON addObject:rangeDict];
    }];
    
    NSArray *chatItems = [chat chatItems];
    
    NSMutableArray *insertedForJSON = [NSMutableArray new];
    [insertedItems enumerateRangesUsingBlock:^(NSRange range, BOOL * _Nonnull stop) {
        NSMutableArray *insertedItems = [NSMutableArray new];
        for (NSUInteger offset = 0; offset < range.length; offset++) {
            IMChatItem *chatItem = chatItems[range.location + offset];
            [insertedItems addObject:[self dictForIMChatItem:chatItem]];
        }
        
        NSDictionary *itemsWithLocationDict = @{
            @"location": @(range.location),
            @"items": insertedItems
        };
        [insertedForJSON addObject:itemsWithLocationDict];
    }];
    
    NSMutableArray *reloadForJSON = [NSMutableArray new];
    [reloadItems enumerateRangesUsingBlock:^(NSRange range, BOOL * _Nonnull stop) {
        NSMutableArray *itemsForJSON = [[NSMutableArray alloc] initWithCapacity:range.length];
        for (NSUInteger offset = 0; offset < range.length; offset++) {
            IMChatItem *item = chatItems[range.location + offset];
            NSDictionary *itemDict = [self dictForIMChatItem:item];
            [itemsForJSON addObject:itemDict];
        }
        
        NSDictionary *itemsWithLocationDict = @{
            @"location": @(range.location),
            @"items": itemsForJSON
        };
        [reloadForJSON addObject:itemsWithLocationDict];
    }];
    
    return @{
        @"chatIdentifier": [chat chatIdentifier],
        @"removedItems": removedForJSON,
        @"insertedItems": insertedForJSON,
        @"reloadItems": reloadForJSON
    };
}

+ (NSDictionary*) dictForIMChatPropertiesChangedNotification:(NSNotification*)notification {
    //look for [IMChat setValue:forChatProperty:]
    //ignoreAlertsFlag
    //EnableReadReceiptForChat
    //full list of allowed properties from undefined function:
    /*
    &cf_SkipAutoJoin,&cf_ignoreAlertsFlag,
    &cf_com.apple.iChat.LastArchivedMessageDate,
    &cf_com.apple.iChat.LastArchivedMessageID,&cf_CKChatConversationKeyboardKey,
    &cf_CKChatWatermarkMessageID,&cf_CKChatWatermarkTime,
    &cf_IMChatWatermarkMessageID,&cf_IMChatWatermarkDate,
    &cf_CKChatLastCanceledMessageTime,&cf_CKChatConsecutiveCanceledMessageCount,
    &cf_CKChatConsecutiveManuallyCanceledMessageCount,
    &cf_CKChatPreviousAccountsDictionaryKey,&cf_com.apple.iChat.UnreadMessagesKey,
    &cf_CKChatUnmuteTime,&cf_LastCanceledMessageTime,
    &cf_ConsecutiveCanceledMessageCount,&cf_ConsecutiveManuallyCanceledMessageCount
    ,&cf_EnableReadReceiptForChat,&cf_EnableReadReceiptForChatVersionID,
    &cf_hasBeenAutoSpamReported,&cf_VIP,&cf_wasAutoDetectedForSpam,
    &cf_wasDetectedAsSMSSpam,&cf_wasDetectedAsiMessageSpam,&cf_smsSpamExtensionName
    ,&cf_numberOfTimesRespondedtoThread,&cf_hasViewedPotentialSpamChat,
    &cf_lastTUConversationCreatedDate,&cf_shouldForceToSMS,
    *(undefined8 *)_IMChatPropertyLastSeenMessageGuid,
    &cf_containsMessageFromContact,&cf_smsHandshakeState,&cf_messageHandshakeState,
    &cf_lastBlackholeReceiptPromptDate
     */
    
    //for now, do nothing
    //later when adding do not disturb and read reciets we will need to use this
    
    return @{};
    /*
    IMChat *chat = [notification object];
    return @{
        @"chatIdentifier": [chat chatIdentifier]
    };
     */
}

+ (NSDictionary*) dictForCNContactStore:(CNContactStore*)contactStore {
    NSMutableDictionary *contacts = [NSMutableDictionary new];
    
    CNContactFormatterStyle contactFormatterStyle = CNContactFormatterStyleFullName;
    CNContactFetchRequest *request = [[CNContactFetchRequest alloc] initWithKeysToFetch:@[CNContactEmailAddressesKey, CNContactPhoneNumbersKey, [CNContactFormatter descriptorForRequiredKeysForStyle:contactFormatterStyle]]];
    NSError *contactsError = nil;
    [contactStore enumerateContactsWithFetchRequest:request error:&contactsError usingBlock:^(CNContact * _Nonnull contact, BOOL * _Nonnull stop) {
        
        NSMutableDictionary *phoneNumbers = [NSMutableDictionary new];
        for (CNLabeledValue *phoneNumberLabelVal in [contact phoneNumbers]) {
            NSString *phoneType = [phoneNumberLabelVal label]; //@"iPhone", @"_$!<Home>!$_", @"_$!<Work>!$_" or a blank NSString
            CNPhoneNumber *phoneNumber = [phoneNumberLabelVal value];
            NSString *phoneNumberStr = [phoneNumber stringValue];
            [phoneNumbers setObject:phoneNumberStr forKey:phoneType];
        }
        
        NSMutableDictionary *emailAddresses = [NSMutableDictionary new];
        for (CNLabeledValue *email in [contact emailAddresses]) {
            //label==work, home, ...
            //value==x@x.com, y@y.co, ...
            [emailAddresses setObject:[email value] forKey:[email label]];
        }
        
        NSString *formattedName = [CNContactFormatter stringFromContact:contact style:contactFormatterStyle];
        [contacts setObject:@{
            @"formattedName": formattedName,
            @"phoneNumbers": phoneNumbers,
            @"emailAddresses": emailAddresses
        } forKey: [contact identifier]];
    }];
    if (contactsError != nil) {
        [NSException raise:@"FetchContactsException" format:@"enumerateContactsWithFetchRequest failed: %@",  contactsError];
    }
    
    return contacts;
}

@end
