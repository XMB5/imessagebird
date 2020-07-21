//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <ProtocolBuffer/PBCodable.h>

#import <IMSharedUtilities/NSCopying-Protocol.h>

@class NSData, NSString;

@interface IMSharedUtilitiesProtoCloudKitEncryptedGroupTitleChange : PBCodable <NSCopying>
{
    NSString *_groupTitle;
    NSString *_otherHandle;
    NSData *_padding;
    unsigned int _version;
    struct {
        unsigned int version:1;
    } _has;
}

@property(retain, nonatomic) NSData *padding; // @synthesize padding=_padding;
@property(retain, nonatomic) NSString *otherHandle; // @synthesize otherHandle=_otherHandle;
@property(retain, nonatomic) NSString *groupTitle; // @synthesize groupTitle=_groupTitle;
@property(nonatomic) unsigned int version; // @synthesize version=_version;
- (void)mergeFrom:(id)arg1;
- (unsigned long long)hash;
- (BOOL)isEqual:(id)arg1;
- (id)copyWithZone:(struct _NSZone *)arg1;
- (void)copyTo:(id)arg1;
- (void)writeTo:(id)arg1;
- (BOOL)readFrom:(id)arg1;
- (id)dictionaryRepresentation;
- (id)description;
@property(readonly, nonatomic) BOOL hasPadding;
@property(readonly, nonatomic) BOOL hasOtherHandle;
@property(readonly, nonatomic) BOOL hasGroupTitle;
@property(nonatomic) BOOL hasVersion;
- (void)dealloc;

@end

