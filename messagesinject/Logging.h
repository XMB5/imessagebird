//
//  Logging.h
//  messagesinject
//
//  Created by Sam Foxman on 7/19/20.
//  Copyright © 2020 organization.name. All rights reserved.
/

#ifndef MESSAGESINJECT_LOGGING_HEADER_IMPORTED
#define MESSAGESINJECT_LOGGING_HEADER_IMPORTED

#import <Foundation/Foundation.h>

//purposefully not INJLogImpl because then it shows up under autocomplete
void implementationOfINJLog(NSString *format, ...);

//#define INJLogPlus(args...) implementationOfINJLogPlus(strrchr("/" __FILE__, '/') + 1, __LINE__, __FUNCTION__, args)
//too much pollution when printing file name, line, and function

#define INJLog(args...) implementationOfINJLog(args)

#endif
