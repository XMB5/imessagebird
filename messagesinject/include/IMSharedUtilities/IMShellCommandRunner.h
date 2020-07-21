//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <objc/NSObject.h>

@class NSError, NSMutableString, NSString;

@interface IMShellCommandRunner : NSObject
{
    NSMutableString *_standardOut;
    NSMutableString *_standardErr;
    int _exitCode;
}

+ (id)runCommand:(id)arg1 args:(id)arg2;
+ (id)runBashScript:(id)arg1 args:(id)arg2;
- (void).cxx_destruct;
@property(readonly) int exitCode; // @synthesize exitCode=_exitCode;
@property(readonly) NSString *standardOut; // @synthesize standardOut=_standardOut;
@property(readonly) NSString *standardErr; // @synthesize standardErr=_standardErr;
@property(readonly) NSError *error;
- (void)run:(id)arg1 args:(id)arg2;
- (void)_setStderrOnTask:(id)arg1;
- (void)_setStdoutOnTask:(id)arg1;
- (id)stringFromPipe:(id)arg1;
- (void)handleStdoutChanged:(id)arg1;

@end
