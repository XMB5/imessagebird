//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <objc/NSObject.h>

@protocol OS_dispatch_queue;

@interface IMLogDump : NSObject
{
    BOOL _shouldCollectPowerWifiStats;
    NSObject<OS_dispatch_queue> *_logDumpQueue;
}

+ (id)sharedInstance;
- (void).cxx_destruct;
@property(readonly, nonatomic) BOOL shouldCollectPowerWifiStats; // @synthesize shouldCollectPowerWifiStats=_shouldCollectPowerWifiStats;
@property(readonly, nonatomic) NSObject<OS_dispatch_queue> *logDumpQueue; // @synthesize logDumpQueue=_logDumpQueue;
- (id)createTodaysStatisticDictionaryIfNeeded;
- (void)_noteSyncEndedForDurationKey:(id)arg1 dateKey:(id)arg2;
- (void)noteAHDASyncEnded;
- (void)noteCoreDuetSyncEnded;
- (void)_incrementSyncAttemptsWithKey:(id)arg1 syncDateKey:(id)arg2;
- (void)incrementAHDASyncAttempts;
- (void)incrementCoreDuetSyncAttempts;
- (void)printPowerAndWifiStats;
- (id)_calculatePowerAndWifiConnectedTimeInMinutesForDictionary:(id)arg1;
- (void)_calculateConnectedMinutesForDateKey:(id)arg1 durationKey:(id)arg2 daysDictionary:(id)arg3 totalDurationDictionary:(id)arg4 totalDurationKey:(id)arg5;
- (BOOL)_isOnPower;
- (BOOL)_isWifiUsable;
- (id)_dictionaryForDayKey:(id)arg1;
- (void)printSyncDurationStats;
- (double)_calculateMinutesSyncingWithDurationKey:(id)arg1 attemptDateKey:(id)arg2;
- (void)printIfWeAreInTheMiddleOfASync;
- (void)clearSyncStats;
- (void)_includeCloudKitDebugFilesAtPath:(id)arg1;
- (id)logShowCommandToFilePath:(id)arg1 lastHours:(int)arg2 predicate:(id)arg3;
- (void)dumpLogsToFolderAtPath:(id)arg1 withFileName:(id)arg2 lastHours:(int)arg3 predicate:(id)arg4 includeCKDebug:(BOOL)arg5 withCompletion:(CDUnknownBlockType)arg6;
- (BOOL)_checkArgumentValidity:(id)arg1 withFileName:(id)arg2 withError:(id *)arg3;
- (void)_compressAndDeleteFilesAtPath:(id)arg1 destinationFilePath:(id)arg2 withCompletion:(CDUnknownBlockType)arg3;
- (void)dumpMOCLoggingMetaData;
- (id)_lastHoursToAppend:(int)arg1;
- (id)_predicateToAppend:(id)arg1;
- (id)init;

@end

