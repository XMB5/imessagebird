//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <IDS/NSObject-Protocol.h>

@class NSArray, NSData, NSDictionary, NSError, NSNumber, NSObject, NSSet, NSString;
@protocol OS_xpc_object;

@protocol IDSDaemonListenerProtocol <NSObject>

@optional
- (void)iMessageReportSpamCheckUnknownResponseForRequestID:(NSString *)arg1 status:(long long)arg2 abusive:(BOOL)arg3 delay:(double)arg4 withError:(NSError *)arg5;
- (void)registrationControlStatusResponseForRequestID:(long long)arg1 requestID:(NSString *)arg2 withError:(NSError *)arg3;
- (void)registrationControlResponseForRequestID:(NSString *)arg1 withError:(NSError *)arg2;
- (void)applecareResponseForRequestID:(NSString *)arg1 withError:(NSError *)arg2;
- (void)localPairingResponseForRequestID:(NSString *)arg1 withError:(NSError *)arg2 pairedDevices:(NSArray *)arg3;
- (void)localPairingResponseForRequestID:(NSString *)arg1 withError:(NSError *)arg2;
- (void)deactivatePairedDevices;
- (void)didSwitchActivePairedDevice:(NSString *)arg1 forService:(NSString *)arg2 wasHandled:(char *)arg3;
- (void)didSwitchActivePairedDevice:(NSString *)arg1;
- (void)deviceIdentifierDidChange:(NSString *)arg1;
- (void)refreshUserAccessTokens:(NSArray *)arg1 error:(NSError *)arg2;
- (void)userAccessTokens:(NSArray *)arg1 error:(NSError *)arg2;
- (void)consentTokens:(NSArray *)arg1 error:(NSError *)arg2;
- (void)adminAccessTokens:(NSArray *)arg1 error:(NSError *)arg2;
- (void)serviceUserIDs:(NSArray *)arg1 error:(NSError *)arg2;
- (void)continuityDidDisconnectFromPeer:(NSString *)arg1 withError:(NSError *)arg2;
- (void)continuityDidConnectToPeer:(NSString *)arg1 withError:(NSError *)arg2;
- (void)continuityDidDiscoverPeerWithData:(NSData *)arg1 fromPeer:(NSString *)arg2;
- (void)continuityDidDiscoverType:(long long)arg1 withData:(NSData *)arg2 fromPeer:(NSString *)arg3;
- (void)continuityDidFailToStartScanningForType:(long long)arg1 withError:(NSError *)arg2;
- (void)continuityDidStopScanningForType:(long long)arg1;
- (void)continuityDidStartScanningForType:(long long)arg1;
- (void)continuityDidFailToStartAdvertisingOfType:(long long)arg1 withError:(NSError *)arg2;
- (void)continuityDidStopAdvertisingOfType:(long long)arg1 withError:(NSError *)arg2;
- (void)continuityDidStopAdvertisingOfType:(long long)arg1;
- (void)continuityDidStartAdvertisingOfType:(long long)arg1;
- (void)continuityDidStopTrackingPeer:(NSString *)arg1 forType:(long long)arg2;
- (void)continuityDidStopTrackingPeer:(NSString *)arg1;
- (void)continuityDidStartTrackingPeer:(NSString *)arg1 forType:(long long)arg2 error:(NSError *)arg3;
- (void)continuityDidStartTrackingPeer:(NSString *)arg1 error:(NSError *)arg2;
- (void)continuityDidLosePeer:(NSString *)arg1 forType:(long long)arg2;
- (void)continuityDidLosePeer:(NSString *)arg1;
- (void)continuityDidUpdateStateToState:(long long)arg1;
- (void)device:(NSString *)arg1 nsuuidChanged:(NSString *)arg2;
- (void)deliveryStats:(NSDictionary *)arg1;
- (void)xpcObject:(NSObject<OS_xpc_object> *)arg1 objectContext:(NSDictionary *)arg2;
- (void)openedSocket:(NSObject<OS_xpc_object> *)arg1 forHandlerID:(NSString *)arg2 error:(NSError *)arg3;
- (void)allocationDone:(NSString *)arg1 sessionInfo:(NSDictionary *)arg2;
- (void)receivedGroupSessionParticipantDataUpdate:(NSDictionary *)arg1 forTopic:(NSString *)arg2 toIdentifier:(NSString *)arg3 fromID:(NSString *)arg4;
- (void)receivedGroupSessionParticipantUpdate:(NSDictionary *)arg1 forTopic:(NSString *)arg2 toIdentifier:(NSString *)arg3 fromID:(NSString *)arg4;
- (void)session:(NSString *)arg1 didReceiveActiveParticipants:(NSArray *)arg2 success:(BOOL)arg3;
- (void)session:(NSString *)arg1 participantDidLeaveGroupWithInfo:(NSDictionary *)arg2;
- (void)session:(NSString *)arg1 participantDidJoinGroupWithInfo:(NSDictionary *)arg2;
- (void)sessionDidLeaveGroup:(NSString *)arg1 error:(NSError *)arg2;
- (void)sessionDidJoinGroup:(NSString *)arg1 participantUpdateDictionary:(NSDictionary *)arg2 error:(NSError *)arg3;
- (void)sessionDidJoinGroup:(NSString *)arg1 participantInfo:(NSDictionary *)arg2 error:(NSError *)arg3;
- (void)sessionDidJoinGroup:(NSString *)arg1 participantsInfo:(NSArray *)arg2 error:(NSError *)arg3;
- (void)session:(NSString *)arg1 didReceiveReport:(NSArray *)arg2;
- (void)session:(NSString *)arg1 muted:(BOOL)arg2;
- (void)session:(NSString *)arg1 audioEnabled:(BOOL)arg2;
- (void)session:(NSString *)arg1 invitationSentToTokens:(NSSet *)arg2 shouldBreakBeforeMake:(BOOL)arg3;
- (void)groupSessionEnded:(NSString *)arg1 withReason:(unsigned int)arg2 error:(NSError *)arg3;
- (void)groupSessionDidTerminate:(NSString *)arg1;
- (void)sessionEnded:(NSString *)arg1 withReason:(unsigned int)arg2 error:(NSError *)arg3;
- (void)sessionStarted:(NSString *)arg1;
- (void)sessionEndReceived:(NSString *)arg1 fromID:(NSString *)arg2 withData:(NSData *)arg3;
- (void)sessionMessageReceived:(NSString *)arg1 fromID:(NSString *)arg2 withData:(NSData *)arg3;
- (void)sessionCancelReceived:(NSString *)arg1 fromID:(NSString *)arg2 withData:(NSData *)arg3;
- (void)sessionDeclineReceived:(NSString *)arg1 fromID:(NSString *)arg2 withData:(NSData *)arg3;
- (void)sessionAcceptReceived:(NSString *)arg1 fromID:(NSString *)arg2 withData:(NSData *)arg3;
- (void)sessionInvitationReceivedWithPayload:(NSDictionary *)arg1 forTopic:(NSString *)arg2 sessionID:(NSString *)arg3 toIdentifier:(NSString *)arg4 fromID:(NSString *)arg5 transportType:(NSNumber *)arg6;
- (void)didFlushCacheForService:(NSString *)arg1 remoteURI:(NSString *)arg2 fromURI:(NSString *)arg3 guid:(NSString *)arg4;
- (void)IDQueryCompletedWithFromURI:(NSString *)arg1 idStatusUpdates:(NSDictionary *)arg2 service:(NSString *)arg3 success:(BOOL)arg4 error:(NSError *)arg5;
- (void)didFetchPhoneUserSubscriptionSource:(NSNumber *)arg1 requestUUID:(NSString *)arg2 error:(NSError *)arg3;
- (void)didSetPhoneUserSubscriptionSource:(NSNumber *)arg1 requestUUID:(NSString *)arg2 error:(NSError *)arg3;
- (void)didRequestCarrierTokenString:(NSString *)arg1 requestUUID:(NSString *)arg2 error:(NSError *)arg3;
- (void)didGeneratePhoneAuthenticationSignature:(NSData *)arg1 nonce:(NSData *)arg2 certificates:(NSArray *)arg3 labelIDs:(NSArray *)arg4 inputData:(NSData *)arg5 requestUUID:(NSString *)arg6 error:(NSError *)arg7;
- (void)didAuthenticatePhoneWithAuthenticationCertificateData:(NSData *)arg1 requestUUID:(NSString *)arg2 error:(NSError *)arg3;
- (void)account:(NSString *)arg1 localDeviceRemoved:(NSDictionary *)arg2;
- (void)account:(NSString *)arg1 localDeviceAdded:(NSDictionary *)arg2;
- (void)account:(NSString *)arg1 dependentDevicesUpdatedUponReconnect:(NSArray *)arg2;
- (void)account:(NSString *)arg1 dependentDevicesUpdated:(NSArray *)arg2;
- (void)updateDeviceIdentity:(NSData *)arg1 error:(NSError *)arg2;
- (void)refreshRegistrationForAccount:(NSString *)arg1;
- (void)registrationFailedForAccount:(NSString *)arg1 needsDeletion:(NSNumber *)arg2;
- (void)account:(NSString *)arg1 displayNameChanged:(NSString *)arg2;
- (void)account:(NSString *)arg1 loginChanged:(NSString *)arg2;
- (void)account:(NSString *)arg1 profileChanged:(NSDictionary *)arg2;
- (void)account:(NSString *)arg1 vettedAliasesChanged:(NSArray *)arg2;
- (void)account:(NSString *)arg1 aliasesChanged:(NSArray *)arg2;
- (void)account:(NSString *)arg1 registrationStatusInfoChanged:(NSDictionary *)arg2;
- (void)account:(NSString *)arg1 accountInfoChanged:(NSDictionary *)arg2;
- (void)setupCompleteForAccount:(NSString *)arg1 transactionID:(NSString *)arg2 setupError:(NSError *)arg3;
- (void)accountDisabled:(NSString *)arg1 onService:(NSString *)arg2;
- (void)accountEnabled:(NSString *)arg1 onService:(NSString *)arg2;
- (void)accountsChanged:(NSArray *)arg1 forTopic:(NSString *)arg2;
- (void)accountUpdated:(NSDictionary *)arg1;
- (void)accountRemoved:(NSDictionary *)arg1;
- (void)accountAdded:(NSDictionary *)arg1;
- (void)checkTransportLogWithReason:(long long)arg1;
- (void)engramDataReceived:(NSDictionary *)arg1 withGUID:(NSString *)arg2 forTopic:(NSString *)arg3 toIdentifier:(NSString *)arg4 fromID:(NSString *)arg5 context:(NSDictionary *)arg6;
- (void)groupShareReceived:(NSData *)arg1 withGUID:(NSString *)arg2 forTopic:(NSString *)arg3 toIdentifier:(NSString *)arg4 fromID:(NSString *)arg5 context:(NSDictionary *)arg6;
- (void)OTRTestCallback:(NSString *)arg1 time:(double)arg2 error:(NSError *)arg3;
- (void)pendingIncomingMessageWithGUID:(NSString *)arg1 forTopic:(NSString *)arg2 toIdentifier:(NSString *)arg3 fromID:(NSString *)arg4 context:(NSDictionary *)arg5;
- (void)protobufReceived:(NSDictionary *)arg1 withGUID:(NSString *)arg2 forTopic:(NSString *)arg3 toIdentifier:(NSString *)arg4 fromID:(NSString *)arg5 context:(NSDictionary *)arg6;
- (void)messageIdentifier:(NSString *)arg1 forTopic:(NSString *)arg2 toIdentifier:(NSString *)arg3 fromIdentifier:(NSString *)arg4 hasBeenDeliveredWithContext:(NSDictionary *)arg5;
- (void)didSendOpportunisticDataWithIdentifier:(NSString *)arg1 onAccount:(NSString *)arg2 toIDs:(NSArray *)arg3;
- (void)messageIdentifier:(NSString *)arg1 alternateCallbackID:(NSString *)arg2 forAccount:(NSString *)arg3 willSendToDestinations:(NSArray *)arg4 skippedDestinations:(NSArray *)arg5 registrationPropertyToDestinations:(NSDictionary *)arg6;
- (void)messageIdentifier:(NSString *)arg1 alternateCallbackID:(NSString *)arg2 forAccount:(NSString *)arg3 updatedWithResponseCode:(long long)arg4 error:(NSError *)arg5 lastCall:(BOOL)arg6 context:(NSDictionary *)arg7;
- (void)accessoryReportMessageReceived:(NSString *)arg1 accessoryID:(NSString *)arg2 controllerID:(NSString *)arg3 withGUID:(NSString *)arg4 forTopic:(NSString *)arg5 toIdentifier:(NSString *)arg6 fromID:(NSString *)arg7 context:(NSDictionary *)arg8;
- (void)accessoryDataReceived:(NSData *)arg1 withGUID:(NSString *)arg2 forTopic:(NSString *)arg3 toIdentifier:(NSString *)arg4 fromID:(NSString *)arg5 context:(NSDictionary *)arg6;
- (void)dataReceived:(NSData *)arg1 withGUID:(NSString *)arg2 forTopic:(NSString *)arg3 toIdentifier:(NSString *)arg4 fromID:(NSString *)arg5 context:(NSDictionary *)arg6;
- (void)messageReceived:(NSDictionary *)arg1 withGUID:(NSString *)arg2 withPayload:(NSDictionary *)arg3 forTopic:(NSString *)arg4 toIdentifier:(NSString *)arg5 fromID:(NSString *)arg6 context:(NSDictionary *)arg7;
- (void)opportunisticDataReceived:(NSData *)arg1 withIdentifier:(NSString *)arg2 fromID:(NSString *)arg3 context:(NSDictionary *)arg4;
- (void)daemonDisconnected;
- (void)daemonConnected;
- (void)setupCompleteWithInfo:(NSDictionary *)arg1;
- (void)connectionComplete:(BOOL)arg1;
@end

