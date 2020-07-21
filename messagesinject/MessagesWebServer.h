//
//  MyWebServer.h
//  messagesinject
//
//  Created by Sam Foxman on 7/6/20.
//  Copyright © 2020 organization.name. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <PSWebSocketServer.h>

NS_ASSUME_NONNULL_BEGIN

@interface MessagesWebServer : NSObject <PSWebSocketServerDelegate>

//If I understand correctly, "atomic" makes it so that reads and writes to a property use a lock/semaphore
//here, we are already using activeWebsocketsLock, so atomic adds an unnecessary extra lock
//not totally sure about this though
@property(nonatomic, strong) NSLock *activeWebsocketsLock;
@property(nonatomic, strong) NSMutableSet *activeWebsockets;

@end

NS_ASSUME_NONNULL_END
