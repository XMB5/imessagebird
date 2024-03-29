//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <IMCore/IMBalloonPlugin.h>

@class LSPlugInKitProxy, NSExtension, NSNumber, NSUUID;
@protocol PKPlugIn;

@interface IMBalloonAppExtension : IMBalloonPlugin
{
    BOOL _canSendDataPayloads;
    BOOL _shouldBalloonHideAppIcon;
    NSExtension *_extension;
    LSPlugInKitProxy *_proxy;
    NSUUID *_requestIdentifier;
}

//- (void).cxx_destruct;
@property(nonatomic) BOOL shouldBalloonHideAppIcon; // @synthesize shouldBalloonHideAppIcon=_shouldBalloonHideAppIcon;
@property(nonatomic) BOOL canSendDataPayloads; // @synthesize canSendDataPayloads=_canSendDataPayloads;
@property NSUUID *requestIdentifier; // @synthesize requestIdentifier=_requestIdentifier;
@property(retain, nonatomic) LSPlugInKitProxy *proxy; // @synthesize proxy=_proxy;
@property(readonly, retain, nonatomic) NSExtension *extension; // @synthesize extension=_extension;
@property(readonly, retain, nonatomic) NSNumber *itemID;
@property(readonly, nonatomic) BOOL isLaunchProhibited;
@property(readonly, retain, nonatomic) id <PKPlugIn> plugin;
- (BOOL)isBetaPlugin;
- (id)version;
- (id)initWithPluginBundle:(id)arg1 appBundle:(id)arg2;
- (id)_initWithPluginBundle:(id)arg1 extension:(id)arg2 pluginKitProxyClass:(Class)arg3;
- (id)initWithPluginBundle:(id)arg1 extension:(id)arg2;
- (id)initWithPluginBundle:(id)arg1 pluginKitProxy:(id)arg2 extension:(id)arg3;

@end

