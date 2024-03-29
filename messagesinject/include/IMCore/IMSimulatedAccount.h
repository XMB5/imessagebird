//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <IMCore/IMAccount.h>

@class IMHandle;

@interface IMSimulatedAccount : IMAccount
{
    IMHandle *_loginHandle;
}

//- (void).cxx_destruct;
@property(retain, nonatomic) IMHandle *loginHandle; // @synthesize loginHandle=_loginHandle;
- (BOOL)isConnected;
- (BOOL)isOperational;
- (BOOL)supportsRegistration;
- (id)loginIMHandle;

@end

