//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <IMCore/IMTranscriptChatItem.h>

@class IMHandle;

@interface IMGroupActionChatItem : IMTranscriptChatItem
{
    IMHandle *_sender;
}

//- (void).cxx_destruct;
@property(readonly, nonatomic) IMHandle *sender; // @synthesize sender=_sender;
- (id)_initWithItem:(id)arg1 sender:(id)arg2;
@property(readonly, nonatomic) long long actionType; //action 0 == "<sender ?? You> left the conversation.", anything else seems to be invalid [ChatItemDOMProvider _parseGroupActionChatItem:]
- (id)copyWithZone:(struct _NSZone *)arg1;

@end

