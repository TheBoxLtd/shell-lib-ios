//
//  ScreenzSDKConfigModel.h
//
//  Copyright (c) 2015 MVD Forge. All rights reserved.
//

#import "JSONModel.h"

/**
 * This instance hold the entire configuration for the app
 * @author Sebastian Castro
 *
 */

@interface ScreenzSDKConfigModel : JSONModel

/**
 * Get the current shared instance. Does not initialize the shared instance, just return the current one or nil if not initialized.
 * @author Sebastian Castro
 *
 * @return The current instance
 */
+ (ScreenzSDKConfigModel *)getInstance;

/**
 * Parse the JSON file and initialize the shared instance. If an instance is already defined, it will return it.
 * @author Sebastian Castro
 *
 * @param fileName File name (with or without extension) of the JSON file (must be a .json file)
 * @return Configuration instance
 */
+ (ScreenzSDKConfigModel *)initInstanceFromJSONFile:(NSString*)fileName;

/**
 * Parse the JSON string and initialize the shared instance. If an instance is already defined, it will return it.
 * @author Sebastian Castro
 *
 * @param json string in JSON format
 * @return Configuration instance
 */
+ (ScreenzSDKConfigModel *)newInstanceFromJSONString:(NSString *)json;

/**
 * Parse the JSON file and initialize.
 * @author Sebastian Castro
 *
 * @param fileName File name (with or without extension) of the JSON file (must be a .json file)
 */
- (id)initFromJSONFile:(NSString*)fileName;

/**
 * Parse the JSON string and initialize.
 * @author Sebastian Castro
 *
 * @param data JSON data forma
 */
- (id)initFromJSONString:(NSString*)data;

//Properties matching JSON data
@property (strong, nonatomic) NSString *site_url_dev;
@property (strong, nonatomic) NSString *api_host_dev;
@property (strong, nonatomic) NSString *site_url_prod;
@property (strong, nonatomic) NSString *api_host_prod;
@property (strong, nonatomic) NSString *preRegister;
@property (strong, nonatomic) NSString *pushReceived;
@property (strong, nonatomic) NSString *getData;
@property (assign, nonatomic) BOOL     location_enabled;
@property (assign, nonatomic) BOOL     autoRotate;
@property (assign, nonatomic) BOOL     landscape;

@property (strong, nonatomic) NSString *wvBgColor;

@end
