//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <objc/NSObject.h>

@class SOCloudKitPurchaseStorageAlertController;

@interface SOCloudKitPurchaseStorageController : NSObject
{
    SOCloudKitPurchaseStorageAlertController *_alertController;
}

+ (id)sharedInstance;
+ (void)__setSingleton__im:(id)arg1;
+ (id)__singleton__im;
- (void).cxx_destruct;
@property(retain) SOCloudKitPurchaseStorageAlertController *alertController; // @synthesize alertController=_alertController;
- (void)beginSheetModalForWindow:(id)arg1 completion:(CDUnknownBlockType)arg2;
@property(readonly, nonatomic) BOOL isPrompting;

@end

