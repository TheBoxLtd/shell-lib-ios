//
//  SchemeValues.h
//  Screenz
//
//  Created by Sebastian Castro on 7/30/15.
//  Copyright (c) 2015 Screenz. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ScreenzSDKSchemeValues : NSObject

@property (assign, nonatomic) BOOL fromScheme;
@property (assign, nonatomic) BOOL qaMode;
@property (assign, nonatomic) NSString* page;
@property (assign, nonatomic) int pid;

/**
 * Get or create the current shared instance
 * @author Sebastian Castro
 *
 * @return The current instance
 */
+ (ScreenzSDKSchemeValues *)sharedInstance;

@end
