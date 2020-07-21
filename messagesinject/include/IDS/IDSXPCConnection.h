//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <objc/NSObject.h>

#import <IDS/NSXPCConnectionDelegate-Protocol.h>

@class NSMutableDictionary, NSString, NSXPCConnection;
@protocol NSXPCProxyCreating, OS_dispatch_queue;

@interface IDSXPCConnection : NSObject <NSXPCConnectionDelegate>
{
    NSObject<OS_dispatch_queue> *_queue;
    NSXPCConnection *_connection;
    NSMutableDictionary *_pendingTransactions;
    IDSXPCConnection *_rootConnection;
    id <NSXPCProxyCreating> _remoteObject;
    CDUnknownBlockType _invalidationHandler;
    BOOL _forSyncMessaging;
}

+ (id)errorForMissingEntitlement:(id)arg1;
- (void).cxx_destruct;
@property(nonatomic) BOOL forSyncMessaging; // @synthesize forSyncMessaging=_forSyncMessaging;
@property(copy, nonatomic) CDUnknownBlockType invalidationHandler; // @synthesize invalidationHandler=_invalidationHandler;
@property(retain, nonatomic) id <NSXPCProxyCreating> remoteObject; // @synthesize remoteObject=_remoteObject;
@property(retain, nonatomic) IDSXPCConnection *rootConnection; // @synthesize rootConnection=_rootConnection;
@property(retain, nonatomic) NSMutableDictionary *pendingTransactions; // @synthesize pendingTransactions=_pendingTransactions;
@property(retain, nonatomic) NSXPCConnection *connection; // @synthesize connection=_connection;
@property(retain, nonatomic) NSObject<OS_dispatch_queue> *queue; // @synthesize queue=_queue;
- (void)_cleanupAllPendingTransactions;
- (void)connection:(id)arg1 handleInvocation:(id)arg2 isReply:(BOOL)arg3;
- (BOOL)hasEntitlement:(id)arg1;
- (id)valueForEntitlement:(id)arg1;
- (id)remoteObjectProxyWithTimeoutInSeconds:(double)arg1 errorHandler:(CDUnknownBlockType)arg2;
- (id)synchronousRemoteObjectProxyWithErrorHandler:(CDUnknownBlockType)arg1;
- (id)remoteObjectProxyWithErrorHandler:(CDUnknownBlockType)arg1;
- (void)dealloc;
- (id)initWithRemoteObject:(id)arg1 rootConnection:(id)arg2;
- (id)_initWithQueue:(id)arg1 takingOverAndResumingConnection:(id)arg2 forSyncMessaging:(BOOL)arg3;
- (id)initWithQueue:(id)arg1 takingOverAndResumingConnection:(id)arg2;
- (id)initForSyncMessagingWithQueue:(id)arg1 takingOverAndResumingConnection:(id)arg2;
- (id)initWithQueue:(id)arg1 remoteObject:(id)arg2;

// Remaining properties
@property(readonly, copy) NSString *debugDescription;
@property(readonly, copy) NSString *description;
@property(readonly) unsigned long long hash;
@property(readonly) Class superclass;

@end
