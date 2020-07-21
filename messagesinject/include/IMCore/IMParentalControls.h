//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <objc/NSObject.h>

@class NSMutableDictionary;

@interface IMParentalControls : NSObject
{
    BOOL _shouldPostNotifications;
    BOOL _active;
    BOOL _disableAV;
    BOOL _forceChatLogging;
    NSMutableDictionary *_parentalControls;
}

+ (id)standardControls;
+ (id)objectForKey:(id)arg1;
//- (void).cxx_destruct;
@property(readonly, nonatomic) BOOL _forceChatLogging; // @synthesize _forceChatLogging;
@property(readonly, nonatomic) BOOL _disableAV; // @synthesize _disableAV;
@property(readonly, nonatomic) NSMutableDictionary *_parentalControls; // @synthesize _parentalControls;
@property(readonly, nonatomic) BOOL active; // @synthesize active=_active;
@property(nonatomic) BOOL shouldPostNotifications; // @synthesize shouldPostNotifications=_shouldPostNotifications;
- (BOOL)accountHasWhitelist:(id)arg1;
- (BOOL)accountIsEnabled:(id)arg1;
- (BOOL)okToConnectAccount:(id)arg1;
- (BOOL)forceWhitelistForAccount:(id)arg1;
- (id)whitelistForAccount:(id)arg1;
- (BOOL)forceWhitelistForService:(id)arg1;
- (id)whitelistForService:(id)arg1;
- (BOOL)disableAccount:(id)arg1;
- (BOOL)disableService:(id)arg1;
@property(readonly, nonatomic) BOOL forceChatLogging;
@property(readonly, nonatomic) BOOL disableAV;
- (void)_managedPrefsNotification:(id)arg1;
- (void)_updateParentalSettings;
- (id)_serviceWithName:(id)arg1;
- (void)dealloc;
- (id)init;

@end

