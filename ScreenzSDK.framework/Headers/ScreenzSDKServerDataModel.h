//
//  ServerDataModel.h
//  Screenz
//
//  Created by Sebastian Castro on 7/28/15.
//  Copyright (c) 2015 Screenz. All rights reserved.
//

#import "JSONModel.h"
#import <UIKit/UIKit.h>

@interface GlossaryModel : JSONModel
@property (strong, nonatomic) NSString *title;
@property (strong, nonatomic) NSString *message;
@property (strong, nonatomic) NSString *ok;
@end

@interface VersionModel : JSONModel
@property (strong, nonatomic) NSString *number;
@property (assign, nonatomic) BOOL is_mandatory;
@property (strong, nonatomic) NSString *alert_title;
@property (strong, nonatomic) NSString *alert_text;
@property (strong, nonatomic) NSString *appstore_link;
@property (strong, nonatomic) NSString *button_positive_text;
@property (strong, nonatomic) NSString *button_negative_text;
@end

@interface MainPageModel : JSONModel
@property (strong, nonatomic) NSString *url;
@end

@interface FullBannerModel : JSONModel
@property (strong, nonatomic) NSString *mobile;
@property (strong, nonatomic) NSString *tablet;
@property (assign, nonatomic) int ttl;
@end

@interface BgImgModel : JSONModel
@property (strong, nonatomic) NSString *medium;
@property (strong, nonatomic) NSString *large;
@end

@interface SplashModel : JSONModel
@property (assign, nonatomic) int ttl;
@property (strong, nonatomic) NSString *type;
@property (strong, nonatomic) BgImgModel<Optional> *bgimg;
@property (strong, nonatomic) NSString *bgcolor;
@property (strong, nonatomic) NSString<Optional> *media;

-(UIColor*)getColor;
@end

/**
 * This instance hold the entire configuration data returned by the server, received in JSON format.
 * @author Sebastian Castro
 *
 */

@interface ScreenzSDKServerDataModel : JSONModel

@property (strong, nonatomic) NSDictionary *glossary;
@property (strong, nonatomic) NSDictionary *version;
@property (strong, nonatomic) MainPageModel<Optional> *main_page;
@property (strong, nonatomic) FullBannerModel<Optional> *full_banner;
@property (strong, nonatomic) SplashModel<Optional> *splash;

/**
 * Get the current shared instance. Does not initialize the shared instance, just return the current one or nil if not initialized.
 * @author Sebastian Castro
 *
 * @return The current instance
 */
+ (ScreenzSDKServerDataModel *)getInstance;

/**
 * Parse the JSON string and initialize the shared instance. If an instance is already defined, it will return it.
 * @author Sebastian Castro
 *
 * @param json string in JSON format
 * @return Configuration instance
 */
+ (ScreenzSDKServerDataModel *)getInstanceFromJSONString:(NSString*)json;

/**
 * Parse the JSON string and initialize.
 * @author Sebastian Castro
 *
 * @param data JSON data forma
 */
- (id)initFromJSONString:(NSString*)data;

/**
 * Get the server version data, it has all the information regarding the latest version available of the app
 * @author Sebastian Castro
 *
 * @return the version data model
 */
-(VersionModel*)getAppVersion;

@end
