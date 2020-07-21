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
#import <IMCore/IMServiceImpl.h>
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

#import <Contacts/Contacts.h>

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

+ (NSDictionary*) dataForIMTextMessagePartChatItem:(IMTextMessagePartChatItem*)item {
    NSMutableArray *attrList = [NSMutableArray new];
    NSAttributedString *text = [item text];
    id textString;
    
    NSLog(@"process attr text %@", text);
    
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

+ (NSDictionary*) dataForIMSenderChatItem:(IMSenderChatItem*)item {
    NSDictionary *handleData = [self dictForIMHandle:[item handle]];
    return @{
        @"handle": handleData
    };
}

+ (NSDictionary*) dataForIMDateChatItem:(IMDateChatItem*)item {
    NSTimeInterval secondsSince1970 = [[item date] timeIntervalSince1970];
    return @{
        @"secondsSince1970": @(secondsSince1970)
    };
}

+ (NSDictionary*) dataForIMServiceChatItem:(IMServiceChatItem*)item {
    IMServiceImpl *service = [item service];
    id serviceNameForJSON = service == nil ? [NSNull null] : [service name];
    
    return @{
        //if both are null, ignore the message (not sure why this happens, may be associated with group title change)
        @"serviceName": serviceNameForJSON, //"iMessage" or "SMS", never localized
        @"handle": [self dictForIMHandle:[item handle]] //ex "iMessage with +1 (800) 123-1231" (not name, even though in contacts)
    };
}

+ (NSDictionary*) dataForIMMessageStatusItem:(IMMessageStatusChatItem*)item {
    return @{
        @"isFromMe": @((bool)[item isFromMe]),
        @"statusType": @([item statusType]),
        @"expireStatusType": @([item expireStatusType])
    };
}

+ (NSDictionary*) dataForIMAttachmentMessagePartChatItem:(IMAttachmentMessagePartChatItem*)item {
    return @{
        @"isFromMe": @((bool)[item isFromMe]),
        @"transferGUID": [item transferGUID]
    };
}

+ (NSDictionary*) dataForIMAudioMessageChatItem:(IMAudioMessageChatItem*)item {
    return @{
        @"isSaved": @((BOOL) [item isSaved]),
        @"isPlayed": @((BOOL)[item isPlayed]),
        @"attachmentMessagePartData": [self dataForIMAttachmentMessagePartChatItem:item]
    };
}

+ (NSDictionary*) dataForIMLoadMoreChatItem:(IMLoadMoreChatItem*)item {
    return @{}; //nothing to display to the user -- when this item is reached, request to load more messages
}

+ (NSDictionary*) dataForIMTranscriptPluginChatItem:(IMTranscriptPluginChatItem*)item {
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

+ (NSDictionary*) dataForIMGroupActionChatItem:(IMGroupActionChatItem*)item {
    //[ChatItemDOMProvider _parseGroupActionChatItem:]
    return @{
        @"actionType": @([item actionType]), //see comment in IMGroupActionChatItem.h
        @"sender": [self dictForIMHandle:[item sender]]
    };
}

+ (NSDictionary*) dataForIMGroupTitleChangeChatItem:(IMGroupTitleChangeChatItem*)item {
    return @{
        @"title": [self jsonSafeNullable:[item title]], //if title==nil, then the title was removed
        @"sender": [self dictForIMHandle:[item sender]] //if sender==nil, then the end user changed the title (displayed as "You named the conversation <title>")
    };
}

+ (NSDictionary*) dataForIMParticipantChangeChatItem:(IMParticipantChangeChatItem*)item {
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

+ (NSDictionary*) dictForIMChatItem:(IMChatItem*)item {
    //see [ChatItemDOMProvider parseChatItem:chat:] and related functions in SocialUI
    //also look at headers matching <IMCore/IM*ChatItem.h>
    
    NSString *type;
    NSDictionary *data;
    NSLog(@"add item class %@", [item className]);
    if ([item isMemberOfClass:[IMTextMessagePartChatItem class]]) {
        type = @"textMessagePart";
        data = [self dataForIMTextMessagePartChatItem:(IMTextMessagePartChatItem*)item];
    } else if ([item isMemberOfClass:[IMSenderChatItem class]]) {
        type = @"sender";
        data = [self dataForIMSenderChatItem:(IMSenderChatItem*)item];
    } else if ([item isMemberOfClass:[IMDateChatItem class]]) {
        type = @"date";
        data = [self dataForIMDateChatItem:(IMDateChatItem*)item];
    } else if ([item isMemberOfClass:[IMServiceChatItem class]]) {
        type = @"service";
        data = [self dataForIMServiceChatItem:(IMServiceChatItem*)item];
    } else if ([item isMemberOfClass:[IMAttachmentMessagePartChatItem class]]) {
        type = @"attachmentMessagePart";
        data = [self dataForIMAttachmentMessagePartChatItem:(IMAttachmentMessagePartChatItem*)item];
    } else if ([item isMemberOfClass:[IMAudioMessageChatItem class]]) {
        type = @"audioMessage";
        data = [self dataForIMAudioMessageChatItem:(IMAudioMessageChatItem*)item];
    } else if ([item isMemberOfClass:[IMLoadMoreChatItem class]]) {
        type = @"loadMore";
        data = [self dataForIMLoadMoreChatItem:(IMLoadMoreChatItem*)item];
    } else if ([item isMemberOfClass:[IMTranscriptPluginChatItem class]]) {
        type = @"transcriptPlugin";
        data = [self dataForIMTranscriptPluginChatItem:(IMTranscriptPluginChatItem*)item];
    } else if ([item isMemberOfClass:[IMMessageStatusChatItem class]]) {
        type = @"messageStatus";
        data = [self dataForIMMessageStatusItem:(IMMessageStatusChatItem*)item];
    } else if ([item isMemberOfClass:[IMGroupActionChatItem class]]) {
        type = @"groupAction";
        data = [self dataForIMGroupActionChatItem:(IMGroupActionChatItem*)item];
    } else if ([item isMemberOfClass:[IMGroupTitleChangeChatItem class]]) {
        type = @"groupTitleChange";
        data = [self dataForIMGroupTitleChangeChatItem:(IMGroupTitleChangeChatItem*)item];
    } else if ([item isMemberOfClass:[IMParticipantChangeChatItem class]]) {
        type = @"participantChange";
        data = [self dataForIMParticipantChangeChatItem:(IMParticipantChangeChatItem*)item];
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

@end
