//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <objc/NSObject.h>

@protocol SODarkWakeHelperDelegate;

@interface SODarkWakeHelper : NSObject
{
    id <SODarkWakeHelperDelegate> _delegate;
    struct __CFRunLoopSource *_ioRunLoopSource;
}

+ (BOOL)screenShieldIsRaised;
- (void).cxx_destruct;
@property(nonatomic) struct __CFRunLoopSource *ioRunLoopSource; // @synthesize ioRunLoopSource=_ioRunLoopSource;
@property __weak id <SODarkWakeHelperDelegate> delegate; // @synthesize delegate=_delegate;
- (void)dealloc;
- (id)init;

@end

