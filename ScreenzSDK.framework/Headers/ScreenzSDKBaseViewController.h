//
//  BaseViewController.h
//  ShellApp
//
//  Created by Sebastian Castro on 6/22/15.
//  Copyright (c) 2015 Screenz. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ScreenzSDKManager.h"
#import "ScreenzSDKMediaUploadModel.h"

@interface ScreenzSDKBaseViewController : UIViewController

/**
 * Initialize the VC using the framework bundle using - initWithNibName:bundle:
 * @author Sebastian Castro
 *
 */

-(instancetype)initVC;

/**
 * Initialize the VC using the framework bundle using - initWithNibName:bundle: and assign the internal SDK Manager instance
 * @author Sebastian Castro
 *
 * @param SDK Manager instance to use in the VC
 */

-(instancetype)initWithInstance:(ScreenzSDKManager*)screenz;

/**
 * Load a WebNavigatiorVC and send the data string to the webpage
 * @author Sebastian Castro
 *
 * @param data to send to the webpage
 */

-(void)loadNavigatorWithData:(NSString*)data;

/**
 * Load the media uploader
 * @author Sebastian Castro
 *
 * @param data info of the uploading
 */

-(void)loadVideoUploaderWithData:(ScreenzSDKMediaUploadModel*)data;

/**
 * Get the current SDK Manager instance. If no Manager is assigned to the VC it returns the shared instance.
 * Always use this method to get the manager to work with.
 * @author Sebastian Castro
 *
 * @return The active Screenz SDK Manager instance
 */

-(ScreenzSDKManager*)getScreenzSDK;

-(void)loadBaseURL;

@end
