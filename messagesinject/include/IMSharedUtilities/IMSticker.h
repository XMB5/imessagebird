//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <objc/NSObject.h>

@class NSData, NSDictionary, NSString, NSURL;

@interface IMSticker : NSObject
{
    NSURL *_fileURL;
    NSString *_stickerGUID;
    NSString *_stickerPackGUID;
    NSString *_accessibilityLabel;
    NSString *_moodCategory;
    NSString *_stickerName;
    NSData *_recipe;
    NSString *_ballonBundleID;
    NSDictionary *_attributionInfo;
}

@property(copy, nonatomic) NSDictionary *attributionInfo; // @synthesize attributionInfo=_attributionInfo;
@property(copy, nonatomic) NSString *ballonBundleID; // @synthesize ballonBundleID=_ballonBundleID;
@property(retain, nonatomic) NSData *recipe; // @synthesize recipe=_recipe;
@property(copy, nonatomic) NSString *stickerName; // @synthesize stickerName=_stickerName;
@property(copy, nonatomic) NSString *moodCategory; // @synthesize moodCategory=_moodCategory;
@property(copy, nonatomic) NSString *accessibilityLabel; // @synthesize accessibilityLabel=_accessibilityLabel;
@property(readonly, copy, nonatomic) NSString *stickerPackGUID; // @synthesize stickerPackGUID=_stickerPackGUID;
@property(readonly, copy, nonatomic) NSString *stickerGUID; // @synthesize stickerGUID=_stickerGUID;
@property(readonly, copy, nonatomic) NSURL *fileURL; // @synthesize fileURL=_fileURL;
- (id)initWithStickerPropertyDictionary:(id)arg1 stickerPackID:(id)arg2 stickerPackBundlePath:(id)arg3;
- (unsigned long long)hash;
- (BOOL)isEqual:(id)arg1;
- (void)dealloc;
- (id)description;
- (id)initWithStickerID:(id)arg1 stickerPackID:(id)arg2 fileURL:(id)arg3 accessibilityLabel:(id)arg4 moodCategory:(id)arg5 stickerName:(id)arg6;
- (id)init;

@end

