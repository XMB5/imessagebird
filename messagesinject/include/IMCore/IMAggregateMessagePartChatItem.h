//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <IMCore/IMTextMessagePartChatItem.h>

@class NSArray;

@interface IMAggregateMessagePartChatItem : IMTextMessagePartChatItem
{
    NSArray *_subparts;
}

//- (void).cxx_destruct;
@property(readonly, copy, nonatomic) NSArray *subparts; // @synthesize subparts=_subparts;
- (id)_initWithItem:(id)arg1 messagePartRange:(struct _NSRange)arg2 subparts:(id)arg3;
- (id)copyWithZone:(struct _NSZone *)arg1;
- (id)description;

@end

