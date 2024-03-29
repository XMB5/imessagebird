//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <IMCore/IMDaemonController.h>

@class NSArray;

@interface IMSimulatedDaemonController : IMDaemonController
{
    NSArray *_listeners;
}

+ (id)dictionaryForChat:(id)arg1;
+ (void)beginSimulatingDaemon;
+ (id)sharedInstance;
//- (void).cxx_destruct;
@property(retain, nonatomic) NSArray *listeners; // @synthesize listeners=_listeners;
- (unsigned int)capabilitiesForListenerID:(id)arg1;
- (BOOL)isConnected;
- (BOOL)connectToDaemonWithLaunch:(BOOL)arg1;
- (BOOL)connectToDaemonWithLaunch:(BOOL)arg1 capabilities:(unsigned int)arg2 blockUntilConnected:(BOOL)arg3;
- (void)sendBalloonPayload:(id)arg1 attachments:(id)arg2 withMessageGUID:(id)arg3 bundleID:(id)arg4;

@end

