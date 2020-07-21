//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <objc/NSObject.h>

#import <IMSharedUtilities/IMSingletonOverriding-Protocol.h>

@class NSString;

@interface IMSingletonOverride : NSObject <IMSingletonOverriding>
{
    id _overriddenSingleton;
}

- (void).cxx_destruct;
@property __weak id overriddenSingleton; // @synthesize overriddenSingleton=_overriddenSingleton;
- (BOOL)shouldInvokeSelector:(SEL)arg1 onSingleton:(id)arg2;
- (void)didOverrideSingleton:(id)arg1;

// Remaining properties
@property(readonly, copy) NSString *debugDescription;
@property(readonly, copy) NSString *description;
@property(readonly) unsigned long long hash;
@property(readonly) Class superclass;

@end
