//
//  ChatItemSerializer.h
//  messagesinject
//
//  Created by Sam Foxman on 7/19/20.
//  Copyright © 2020 organization.name. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <IMCore/IMChatItem.h>

NS_ASSUME_NONNULL_BEGIN

@interface ChatSerializer : NSObject

+ (NSString*) stringify:(NSDictionary*)dict;
+ (id) jsonSafeNullable:(id)obj;
+ (NSDictionary*) dataForIMHandle:(IMHandle*)handle;
+ (NSDictionary*) dataForIMChatItem:(IMChatItem*)item;

@end

NS_ASSUME_NONNULL_END
