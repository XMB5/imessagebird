//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <IDS/IDSTransactionLogTaskHandler.h>

@class IDSTransactionLogTask, NSObject;
@protocol OS_dispatch_queue;

@interface IDSTransactionLogBaseTaskHandler : IDSTransactionLogTaskHandler
{
    IDSTransactionLogTask *_task;
    NSObject<OS_dispatch_queue> *_queue;
}

- (void).cxx_destruct;
@property(retain, nonatomic) NSObject<OS_dispatch_queue> *queue; // @synthesize queue=_queue;
@property(retain, nonatomic) IDSTransactionLogTask *task; // @synthesize task=_task;
- (void)perform;
- (id)initWithTask:(id)arg1 delegate:(id)arg2 queue:(id)arg3;

@end
