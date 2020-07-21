//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <objc/NSObject.h>

@class NSData, NSDictionary, NSNumber, NSString, NSURL;

@interface IMRecentItem : NSObject
{
    NSNumber *_timestamp;
    NSString *_GUID;
    NSURL *_fileURL;
    NSData *_payloadData;
    NSDictionary *_messageItemInfo;
    NSString *_accessibilityString;
}

@property(retain, nonatomic) NSString *accessibilityString; // @synthesize accessibilityString=_accessibilityString;
@property(retain, nonatomic) NSDictionary *messageItemInfo; // @synthesize messageItemInfo=_messageItemInfo;
@property(retain, nonatomic) NSNumber *timestamp; // @synthesize timestamp=_timestamp;
@property(retain, nonatomic) NSData *payloadData; // @synthesize payloadData=_payloadData;
@property(retain, nonatomic) NSURL *fileURL; // @synthesize fileURL=_fileURL;
@property(copy, nonatomic) NSString *GUID; // @synthesize GUID=_GUID;
- (id)asJSONObject;
- (unsigned long long)hash;
- (BOOL)isEqual:(id)arg1;
- (id)initWithGUID:(id)arg1 data:(id)arg2 messageItemInfo:(id)arg3;
- (void)dealloc;

@end

