//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <objc/NSObject.h>

@class NSMutableArray, NSString;

@interface SOPerfCounter : NSObject
{
    BOOL _isActive;
    double _lastStartTime;
    NSMutableArray *_times;
    NSString *_name;
    double _longestTime;
    double _timeTally;
}

+ (void)finishTimingForSignpost:(id)arg1;
+ (void)beginTimingForSignpost:(id)arg1;
+ (id)formatTimeList:(id)arg1;
+ (id)formatList:(id)arg1;
+ (id)counterForName:(id)arg1;
+ (id)activeTimings;
+ (id)allTimings;
- (void).cxx_destruct;
@property(nonatomic) double timeTally; // @synthesize timeTally=_timeTally;
@property(nonatomic) double longestTime; // @synthesize longestTime=_longestTime;
@property(nonatomic) BOOL isActive; // @synthesize isActive=_isActive;
@property(retain, nonatomic) NSString *name; // @synthesize name=_name;
@property(retain, nonatomic) NSMutableArray *times; // @synthesize times=_times;
@property(nonatomic) double lastStartTime; // @synthesize lastStartTime=_lastStartTime;
- (void)stop;
- (void)start;
- (id)description;
- (id)init;

@end

