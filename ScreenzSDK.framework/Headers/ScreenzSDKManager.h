//
//  ScreenzSDKManager.h
//  ScreenzSDK
//
//  Created by Sebastian Castro on 2/10/16.
//  Copyright © 2016 Screenz. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ScreenzSDKConfigModel.h"
#import "ScreenzSDKAppConfigModel.h"
#import "ScreenzSDKServerDataModel.h"
#import "ScreenzSDKSchemeValues.h"

@import CoreLocation;

/**
 * This manager provides an unified entry point for the framework.
 * Was build to provide all the functionality for the framework and provide options to use it as a shared instance
 * accros the entire application, or to create multiple instance to handle different SDK intances independently.
 *
 * @author Sebastian Castro
 */

@protocol ScreenzSDKManagerDelegate
-(void)ScreenzSDKManagerDelegate_dataReceived:(NSString*)data;
@end

@interface ScreenzSDKManager : NSObject

@property (nonatomic,retain,readonly) ScreenzSDKAppConfigModel* appConfiguration;
@property (nonatomic,retain,readonly) ScreenzSDKConfigModel* sdkConfiguration;
@property (nonatomic,retain,readonly) ScreenzSDKServerDataModel* serverData;
@property (nonatomic,retain,readonly) ScreenzSDKSchemeValues* schemeValues;

@property (strong, nonatomic, readonly) NSString *carrier;
@property (strong, nonatomic, readonly) NSString *device;
@property (strong, nonatomic, readonly) NSString *language;
@property (strong, nonatomic) CLLocation *currentLocation;
@property (strong, nonatomic, readonly) NSString* udid;

/**
 * Get or create the current shared instance
 * @author Sebastian Castro
 *
 * @return The current instance
 */
+ (ScreenzSDKManager *)sharedInstance;

/**
 * Parse the JSON file and initialize configuration model.
 * @author Sebastian Castro
 *
 * @param fileName File name (with or without extension) of the JSON file (must be a .json file)
 * @return YES if the configuration is correctly loaded, NO on error (configuration set as nil)
 */
-(BOOL)loadConfigurationFromJSONFile:(NSString*)fileName;

/**
 * Parse the JSON string and initialize configuration model.
 * @author Sebastian Castro
 *
 * @param json string in JSON format
 * @return YES if the configuration is correctly loaded, NO on error (configuration set as nil)
 */
-(BOOL)loadConfigurationFromJSONString:(NSString*)json;

/**
 * Parse the JSON string and initialize server data model.
 * @author Sebastian Castro
 *
 * @param json string in JSON format
 * @return YES if model is correctly loaded, NO on error (model set as nil)
 */
-(BOOL)loadServerDataFromJSONString:(NSString*)json;

/**
 * Methods to handle push notifications
 */
-(void)receiveRemoteNotificationWithData:(NSDictionary *)userInfo applicationState:(UIApplicationState)appState completionHandler:(void (^)(UIBackgroundFetchResult))completionHandler;
-(void)registerUserNotification;
-(void)registerForRemoteNotificationsWithToken:(NSData *)deviceToken;
-(void)failtRegisterForRemoteNotifications;

/**
 * Handle the open from url process within the app
 */
-(BOOL)processApplicaitonOpenURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation configurationFile:(NSString*)configFile  viewController:(UIViewController*)vc;

/**
 * Handle the open from url process within the app
 */
-(BOOL)processApplicaitonOpenURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options configurationFile:(NSString *)configFile  viewController:(UIViewController*)vc;

/**
 * Notifies the manager that something in the configuration has changed
 */
-(void)configurationChanged;

/**
 * Rerurn the current PID
 */
-(int)getCurrentPID;


/**
 * Rerurn the current PID as NSNumber
 */
-(NSNumber *)getCurrentPIDAsNumber;

/**
 * Sets the current pid, if valid
 *
 * @param pid to set
 * @return YES if the pid is correct and changed, NO in other case
 */
-(BOOL)changeCurrentPID:(int)pid;


/**
 * Sets extra data to read by the web-app
 *
 * @param data(as string) to store
 */
-(void)setExtraData:(NSString*)data;

/**
 * Sets the pageId the webview should open on launch
 *
 * @param data(as string) to store
 */
-(void)setLaunchPageID:(NSString*)data;

/**
 * Start the loading process of the UI in the View and View Controller specified
 *
 * @param view where the framework UI should be shown
 * @param view ctroller that host the view
 */
-(void)loadInView:(UIView*)view viewController:(UIViewController*)vc;

-(void)reloadWebContainer;

-(void)setDelegate:(id<ScreenzSDKManagerDelegate>)delegate;
-(id<ScreenzSDKManagerDelegate>)getDelegate;
@end

