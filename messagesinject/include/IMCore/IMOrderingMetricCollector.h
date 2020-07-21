//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <objc/NSObject.h>

@protocol OS_dispatch_queue;

@interface IMOrderingMetricCollector : NSObject
{
    BOOL _needToSubmitMetric;
    NSObject<OS_dispatch_queue> *_orderingMetricQueue;
    unsigned long long _numberOfMessagesSeen;
    unsigned long long _numberOfMessagesPlacedOutOfOrder;
    unsigned long long _numberOfMessagesPlacedCorrectly;
}

+ (id)sharedInstance;
//- (void).cxx_destruct;
@property(nonatomic) BOOL needToSubmitMetric; // @synthesize needToSubmitMetric=_needToSubmitMetric;
@property(nonatomic) unsigned long long numberOfMessagesPlacedCorrectly; // @synthesize numberOfMessagesPlacedCorrectly=_numberOfMessagesPlacedCorrectly;
@property(nonatomic) unsigned long long numberOfMessagesPlacedOutOfOrder; // @synthesize numberOfMessagesPlacedOutOfOrder=_numberOfMessagesPlacedOutOfOrder;
@property(nonatomic) unsigned long long numberOfMessagesSeen; // @synthesize numberOfMessagesSeen=_numberOfMessagesSeen;
@property(readonly, nonatomic) NSObject<OS_dispatch_queue> *orderingMetricQueue; // @synthesize orderingMetricQueue=_orderingMetricQueue;
- (void)_persistMetric;
- (void)_submitMetric;
- (void)_submitMetricIfNeeded;
- (void)metricHistoryQueryOrder:(id)arg1;
- (void)_metricHistoryQueryOrder:(id)arg1;
- (BOOL)_metricIncomingMessage:(id)arg1 items:(id)arg2;
- (void)metricIncomingMessage:(id)arg1 items:(id)arg2;
- (void)dealloc;
- (id)init;

@end
