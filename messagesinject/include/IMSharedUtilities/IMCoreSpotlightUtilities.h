//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <objc/NSObject.h>

@interface IMCoreSpotlightUtilities : NSObject
{
}

+ (id)descriptionForReindexReason:(unsigned long long)arg1;
+ (BOOL)bypassIndexVersionCheck;
+ (unsigned long long)messageIndexBatchSize:(BOOL)arg1;
+ (unsigned long long)expectedIndexVersion;
+ (unsigned long long)currentIndexVersion;
+ (unsigned long long)lastIndexedRowID;
+ (void)setNeedsDeferredIndexing;
+ (BOOL)needsDeferredIndexing;
+ (BOOL)needsIndexing;

@end

