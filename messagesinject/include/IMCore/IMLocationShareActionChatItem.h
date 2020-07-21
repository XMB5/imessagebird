//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <IMCore/IMTranscriptChatItem.h>

@class IMHandle;

@interface IMLocationShareActionChatItem : IMTranscriptChatItem
{
    IMHandle *_sender;
    IMHandle *_otherHandle;
}

//- (void).cxx_destruct;
@property(readonly, nonatomic) IMHandle *otherHandle; // @synthesize otherHandle=_otherHandle;
@property(readonly, nonatomic) IMHandle *sender; // @synthesize sender=_sender;
- (id)_initWithItem:(id)arg1 sender:(id)arg2 otherHandle:(id)arg3;
@property(readonly, nonatomic) long long direction;
@property(readonly, nonatomic) long long actionType;
@property(readonly, nonatomic) BOOL isFromMe;
- (id)copyWithZone:(struct _NSZone *)arg1;

@end

