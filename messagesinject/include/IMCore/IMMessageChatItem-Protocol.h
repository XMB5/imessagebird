//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <Foundation/Foundation.h>

@class IMHandle, NSDate;

@protocol IMMessageChatItem <NSObject>
@property(readonly, nonatomic) IMHandle *sender;
@property(readonly, nonatomic) NSDate *time;
@property(readonly, nonatomic) BOOL failed;
@property(readonly, nonatomic) BOOL isFromMe;
@end

