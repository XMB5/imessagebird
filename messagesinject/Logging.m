//
//  Logging.m
//  messagesinject
//
//  Created by Sam Foxman on 7/19/20.
//  Copyright © 2020 organization.name. All rights reserved.
//

#import "Logging.h"

void implementationOfINJLog(NSString *format, ...) {
    va_list args;
    va_start(args, format);
    NSString *formattedStr = [[NSString alloc] initWithFormat:format arguments:args];
    va_end(args);
    
    NSLog(@"[messagesinject] %@", formattedStr);
}
