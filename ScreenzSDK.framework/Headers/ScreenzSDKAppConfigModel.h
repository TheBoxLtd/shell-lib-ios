//
//  ScreenzSDKAppConfigModel.h
//
//  Copyright (c) 2015 MVD Forge. All rights reserved.
//

#import "JSONModel.h"
#import "ScreenzSDKSchemeValues.h"

/**
 * This instance hold the entire configuration for the app
 * @author Sebastian Castro
 *
 */

@interface ScreenzSDKAppConfigModel : JSONModel

/**
 * Get the current shared instance. Does not initialize the shared instance, just return the current one or nil if not initialized.
 * @author Sebastian Castro
 *
 * @return The current instance
 */
+ (ScreenzSDKAppConfigModel *)getInstance;

/**
 * Parse the JSON file and initialize the shared instance. If an instance is already defined, it will return it.
 * @author Sebastian Castro
 *
 * @param fileName File name (with or without extension) of the JSON file (must be a .json file)
 * @return Configuration instance
 */
+ (ScreenzSDKAppConfigModel *)initInstanceFromJSONFile:(NSString*)fileName withScheme:(ScreenzSDKSchemeValues*)scheme;

/**
 * Parse the JSON string and initialize the shared instance. If an instance is already defined, it will return it.
 * @author Sebastian Castro
 *
 * @param json string in JSON format
 * @return Configuration instance
 */
+ (ScreenzSDKAppConfigModel *)newInstanceFromJSONString:(NSString *)json;

/**
 * Parse the JSON file and initialize.
 * @author Sebastian Castro
 *
 * @param fileName File name (with or without extension) of the JSON file (must be a .json file)
 */
- (id)initFromJSONFile:(NSString*)fileName withScheme:(ScreenzSDKSchemeValues*)scheme;

/**
 * Parse the JSON string and initialize.
 * @author Sebastian Castro
 *
 * @param data JSON data forma
 */
- (id)initFromJSONString:(NSString*)data withScheme:(ScreenzSDKSchemeValues*)scheme;


/**
 * Validate is the pid is part of the pid array, which in that case is a valid pid to use
 * @author Sebastian Castro
 *
 * @param pid to validate
 */
-(BOOL)isValidPID:(int)pid;

//Properties matching JSON data
@property (nonatomic) NSArray<NSNumber*> *pids;
@property (nonatomic) int splashDelay;

@property (assign, nonatomic) BOOL     notifications_enabled;
@property (strong, nonatomic) NSString *web_data_mode;

@property (strong, nonatomic) NSString *noConnectionError;

@property (strong, nonatomic) NSString *haKey;

@property (strong, nonatomic) NSString *appsFlyerKey;
@property (strong, nonatomic) NSString *appleAppID;

@property (strong, nonatomic) NSString *apiBaseURL;
@property (strong, nonatomic) NSString *webviewURL;
@property (strong, nonatomic) NSString *video_upload_key;

@property (assign, nonatomic) BOOL     dev_env;
@property (assign, nonatomic) BOOL     useOnPageLoaded;
@property (assign, nonatomic) BOOL     enableQADialog;

@end
