//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <Foundation/NSProxy.h>

@interface IMSingletonProxy : NSProxy
{
    id _singleton;
    id _singletonOverride;
    Class _overrideClass;
}

+ (void)load;
- (void).cxx_destruct;
- (id)description;
- (void)setSingletonOverride:(id)arg1;
- (id)methodSignatureForSelector:(SEL)arg1;
- (void)forwardInvocation:(id)arg1;
- (id)initWithSingleton:(id)arg1 singletonOverride:(id)arg2;
- (id)singletonOverrideRef;
- (id)singletonRef;
- (BOOL)__isSingletonProxy__im;

@end

