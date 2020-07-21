//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <objc/NSObject.h>

@class NSData, NSUUID;

@interface _IDSDataChannelLinkContext : NSObject
{
    BOOL _linkID;
    unsigned char _networkType;
    long long _connectionType;
    unsigned int _RATType;
    unsigned short _maxMTU;
    unsigned char _remoteNetworkType;
    long long _remoteConnectionType;
    unsigned int _remoteRATType;
    unsigned int _maxBitrate;
    NSUUID *_linkUUID;
    NSUUID *_QRSessionID;
    long long _relayServerProvider;
    NSData *_relaySessionToken;
    NSData *_relaySessionKey;
    BOOL _serverIsDegraded;
    unsigned short _localLinkFlags;
    unsigned short _remoteLinkFlags;
}

- (void).cxx_destruct;
- (id)description;

@end
