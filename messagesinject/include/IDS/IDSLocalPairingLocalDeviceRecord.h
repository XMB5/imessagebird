//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <IDS/IDSLocalPairingRecord.h>

#import <IDS/NSSecureCoding-Protocol.h>

@interface IDSLocalPairingLocalDeviceRecord : IDSLocalPairingRecord <NSSecureCoding>
{
}

+ (BOOL)supportsSecureCoding;
- (id)fullIdentityClassD:(id *)arg1;
- (id)fullIdentityClassC:(id *)arg1;
- (id)fullIdentityClassA:(id *)arg1;
- (id)_fullIdenityForDataProtectionClass:(unsigned int)arg1 error:(id *)arg2;
- (id)description;
- (id)initWithWithFullIdentityDataClassA:(id)arg1 classC:(id)arg2 classD:(id)arg3;

@end

