//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <objc/NSObject.h>

@class NSString;

@interface SOIDSListener : NSObject
{
    long long _listenCount;
    NSString *_listenerID;
}

+ (id)sharedListener;
//- (void).cxx_destruct;
@property(readonly) NSString *listenerID; // @synthesize listenerID=_listenerID;
- (id)init;
- (long long)queryKnownIDStatusForDestinations:(id)arg1 service:(id)arg2 completionBlock:(id)arg3;
- (void)endListening;
- (void)beginListening;

@end

