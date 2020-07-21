//
//     Generated by class-dump 3.5 (64 bit).
//
//  Copyright (C) 1997-2019 Steve Nygard.
//

#import <IMCore/IMAccountController.h>

@interface IMAccountController (SocialAppsCoreAdditions)
- (BOOL)load;
- (void)_sortAccounts;
- (BOOL)save;
- (void)_saveSortedAccounts;
- (id)connectedSiblingsForAccount:(id)arg1;
- (BOOL)insertAccount:(id)arg1 atIndex:(unsigned long long)arg2;
- (id)sortOrderForAccounts:(id)arg1;
- (BOOL)hasConnectedAccounts;
- (unsigned long long)myStatus;
- (id)accountForService:(id)arg1 withConferenceName:(id)arg2;
- (id)bestAccountForServiceWithABProperty:(id)arg1;
- (BOOL)hasActiveLegacyAccount;
- (id)accountsSupportingStatus;
- (BOOL)iMessageAccountIsDisabled:(id)arg1;
- (void)addiMessageAccountIfNeeded;
- (void)_deleteExtraiMessageAccounts;
- (void)deleteiMessageAccount:(id)arg1;
@end
