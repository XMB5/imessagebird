//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <objc/NSObject.h>

@class IMAccount;

@interface IMCoreAutomationHook : NSObject
{
    IMAccount *_imessageAccount;
}

+ (id)stringFromAutomationErrorCode:(long long)arg1;
//- (void).cxx_destruct;
- (id)existingChatForGroupID:(id)arg1 error:(id *)arg2 results:(id)arg3;
- (id)handlesFromStrings:(id)arg1 error:(id *)arg2 results:(id)arg3;
- (id)chatForHandles:(id)arg1 error:(id *)arg2 results:(id)arg3;
@property(readonly) IMAccount *bestiMessageAccount;

@end

