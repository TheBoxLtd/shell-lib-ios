//
//  ScreenzSDKMediaUploadModel.h
//  ScreenzSDK
//
//  Created by Sebastian Castro on 10/14/16.
//  Copyright © 2016 Screenz. All rights reserved.
//

#import "JSONModel.h"

@interface ScreenzSDKMediaUploadModel : JSONModel
@property (strong, nonatomic) NSString *camera_uuid;
@property (strong, nonatomic) NSString *api_key;
@property (strong, nonatomic) NSString *url;
@property (strong, nonatomic) NSString *type;
@property (strong, nonatomic) NSString *name;
@property (strong, nonatomic) NSString *dsc;
@property (assign, nonatomic) int minLength;
@property (assign, nonatomic) int maxLength;
@property (strong, nonatomic) NSString *minLengthError;
@property (strong, nonatomic) NSString *maxLengthError;
@property (strong, nonatomic) NSString *genericError;
@property (strong, nonatomic) NSDictionary *metadata;

-(NSString*)getUrl;
-(NSString*)getMetadataAsJsonString;
@end
