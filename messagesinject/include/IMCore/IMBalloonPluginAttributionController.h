//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <objc/NSObject.h>

@class NSMutableDictionary;

@interface IMBalloonPluginAttributionController : NSObject
{
    BOOL _hasPerformedFirstAppExtensionLoad;
    NSMutableDictionary *_expiredBundleIDToTimestampMap;
    NSMutableDictionary *_bundleIDsDisplayingAttribution;
}

+ (id)sharedInstance;
//- (void).cxx_destruct;
@property(nonatomic) BOOL hasPerformedFirstAppExtensionLoad; // @synthesize hasPerformedFirstAppExtensionLoad=_hasPerformedFirstAppExtensionLoad;
@property(retain, nonatomic) NSMutableDictionary *bundleIDsDisplayingAttribution; // @synthesize bundleIDsDisplayingAttribution=_bundleIDsDisplayingAttribution;
@property(retain, nonatomic) NSMutableDictionary *expiredBundleIDToTimestampMap; // @synthesize expiredBundleIDToTimestampMap=_expiredBundleIDToTimestampMap;
- (void)_handleInstalledPluginsChanged;
- (void)_purgeLeastRecentlySeenAppBundleIDsIfNecessary;
- (void)_saveToFile;
- (double)_expiryTimeout;
- (id)_currentTimestamp;
- (BOOL)shouldShowAttributionForBundleID:(id)arg1;
- (void)didShowAttributionForBundleIDs:(id)arg1;
- (void)startExpiryTimer;
- (void)dealloc;
- (id)init;

@end

