//
//  ChatItemSerializer.h
//  messagesinject
//
//  Created by Sam Foxman on 7/19/20.
//  Copyright © 2020 organization.name. All rights reserved.
//

#import <Foundation/Foundation.h>

@class IMHandle, IMChatItem, IMChat;

NS_ASSUME_NONNULL_BEGIN

@interface Serializer : NSObject

+ (NSString*) stringify:(NSDictionary*)dict;
+ (id) jsonSafeNullable:(id)obj;
+ (NSDictionary*) dictForIMHandle:(IMHandle*)handle;
+ (NSDictionary*) dictForIMChatItem:(IMChatItem*)item;
+ (NSDictionary*) dictForIMChat:(IMChat*)chat;

@end

NS_ASSUME_NONNULL_END
