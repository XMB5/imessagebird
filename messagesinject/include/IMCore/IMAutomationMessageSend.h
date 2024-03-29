//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <objc/NSObject.h>

@class NSMutableDictionary, NSMutableSet;

@interface IMAutomationMessageSend : NSObject
{
    NSMutableSet *_pendingSendGUIDs;
    NSMutableDictionary *_sentMessageInfo;
}

//- (void).cxx_destruct;
@property(retain, nonatomic) NSMutableDictionary *sentMessageInfo; // @synthesize sentMessageInfo=_sentMessageInfo;
@property(retain, nonatomic) NSMutableSet *pendingSendGUIDs; // @synthesize pendingSendGUIDs=_pendingSendGUIDs;
- (id)dictionaryFromGUID:(id)arg1;
- (id)fileSizeForMessageGUID:(id)arg1 withFilePathIndex:(long long)arg2;
- (id)uploadAttachmentToCloudkitWithMessageGUID:(id)arg1 andFilePathIndex:(long long)arg2;
- (id)clearAttachmentsUploadedToCloudkit;
- (id)deleteAttachmentWithMessageGUID:(id)arg1 andFilePathIndex:(long long)arg2;
- (id)loadHighResolutionFileForMessageGUID:(id)arg1 withFilePathIndex:(long long)arg2;
- (id)sendIMMessage:(id)arg1 chat:(id)arg2 timeOut:(double)arg3 resultDict:(id)arg4 error:(id *)arg5;
- (id)sendMessage:(id)arg1 destinationID:(id)arg2 filePaths:(id)arg3 isAudioMessage:(BOOL)arg4 groupID:(id)arg5 bundleID:(id)arg6 attributionInfoName:(id)arg7 service:(id)arg8 timeOut:(double)arg9 error:(id *)arg10;
- (id)sendMessage:(id)arg1 destinationID:(id)arg2 filePaths:(id)arg3 groupID:(id)arg4 bundleID:(id)arg5 attributionInfoName:(id)arg6 service:(id)arg7 timeOut:(double)arg8 error:(id *)arg9;
- (id)sendMessage:(id)arg1 destinationID:(id)arg2 filePaths:(id)arg3 groupID:(id)arg4 service:(id)arg5 timeOut:(double)arg6 error:(id *)arg7;
- (id)createIMMessageToSendWithMessage:(id)arg1 filePaths:(id)arg2 bundleID:(id)arg3 attributionInfoName:(id)arg4 isAudioMessage:(BOOL)arg5;
- (id)init;
- (id)appendFilePathsWithGUIDs:(id)arg1 withText:(id)arg2;
- (void)deleteTmpFilePath:(id)arg1;
- (id)copyFilePathsToTmpLocation:(id)arg1;

@end

