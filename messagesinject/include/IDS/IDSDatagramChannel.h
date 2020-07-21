//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <objc/NSObject.h>

@class IDSDataChannelLinkContext, NSArray, _IDSDatagramChannel;

@interface IDSDatagramChannel : NSObject
{
    _IDSDatagramChannel *_internal;
}

+ (id)realTimeContext;
- (void).cxx_destruct;
- (void)osChannelInfoLog;
- (void)generateMetadataWithDatagramInfo:(CDStruct_54fea20c)arg1 options:(CDStruct_6bf83f29 *)arg2 currentDatagramCount:(unsigned char)arg3 totalDatagramCount:(unsigned char)arg4 byteBuffer:(CDStruct_457e09f6 *)arg5;
- (void)_reportFirstPacketTimeForMKI:(id)arg1;
- (void)reportFirstPacketTimeForMKI:(id)arg1;
- (void)requestSessionInfoWithOptions:(id)arg1;
- (void)stopActiveProbingOnLinks:(id)arg1;
- (void)startActiveProbingOnLinks:(id)arg1 interval:(unsigned int)arg2 timeout:(unsigned int)arg3;
- (void)setWiFiAssist:(BOOL)arg1;
- (CDStruct_bd451bc7 *)_setWiFiAssist:(BOOL)arg1;
- (void)setChannelPreferences:(id)arg1;
- (void)_buildPacketBufferMetaData:(CDStruct_bd451bc7 *)arg1;
- (void)sendMetadata;
- (void)readyToRead;
- (void)setReadHandlerWithOptions:(CDUnknownBlockType)arg1;
- (void)setReadHandler:(CDUnknownBlockType)arg1;
- (void)setEventHandler:(CDUnknownBlockType)arg1;
- (void)writeDatagram:(const void *)arg1 datagramSize:(unsigned int)arg2 datagramInfo:(CDStruct_54fea20c)arg3 options:(CDStruct_6bf83f29 *)arg4 completionHandler:(CDUnknownBlockType)arg5;
- (void)writeDatagram:(const void *)arg1 datagramSize:(unsigned int)arg2 flags:(CDStruct_54fea20c)arg3 completionHandler:(CDUnknownBlockType)arg4;
- (void)_writeDatagram:(const void *)arg1 datagramSize:(unsigned int)arg2 datagramInfo:(CDStruct_54fea20c)arg3 options:(CDStruct_6bf83f29 *)arg4 completionHandler:(CDUnknownBlockType)arg5;
- (void)writeDatagrams:(const void **)arg1 datagramSizes:(unsigned int *)arg2 datagramInfo:(CDStruct_54fea20c)arg3 datagramCount:(int)arg4 options:(CDStruct_6bf83f29 *)arg5 completionHandler:(CDUnknownBlockType)arg6;
- (void)writeDatagrams:(const void **)arg1 datagramsSize:(unsigned int *)arg2 datagramsInfo:(CDStruct_54fea20c *)arg3 datagramsCount:(int)arg4 options:(struct **)arg5 completionHandler:(CDUnknownBlockType)arg6;
- (void)start;
- (void)invalidate;
- (void)close;
- (void)readDatagramsWithCompletionHandler:(CDUnknownBlockType)arg1;
- (void)readDatagramWithCompletionHandler:(CDUnknownBlockType)arg1;
- (void)processMetadataForDatagram:(char *)arg1 size:(unsigned long long)arg2 datagramInfo:(CDStruct_54fea20c *)arg3 options:(CDStruct_6bf83f29 *)arg4;
- (void)sendMediaMembershipChangedInfo:(unsigned char)arg1;
- (void)sendMediaEncryptionInfoWithMKM:(id)arg1 MKS:(id)arg2 MKI:(id)arg3 isLocallyGenerated:(BOOL)arg4;
- (void)selectDefaultLink:(BOOL)arg1;
- (void)addNewIDSDataChannelLinkWithAttributes:(char *)arg1 linkAttributesLength:(unsigned short)arg2;
- (void)removeIDSDataChannelLinkContext:(BOOL)arg1 linkUUID:(id)arg2;
- (void)sendEventConnectedWithDummyLinkInfo;
- (int)underlyingFileDescriptor;
- (void)_logReceivingStats:(unsigned long long)arg1;
- (void)_logSendingStats:(unsigned long long)arg1;
- (id)description;
- (void)dealloc;
- (id)cachedMetadata;
- (id)initWithDestination:(id)arg1;
- (id)initWithSocketDescriptor:(int)arg1;
@property(readonly) IDSDataChannelLinkContext *defaultLink;
@property(readonly) NSArray *connectedLinks;

@end

