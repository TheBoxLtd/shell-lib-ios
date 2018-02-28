# Screenz iOS SDK

Screenz SDK allows for the implementation of your own Screenz client that will live in the Screenz environment.

This environment needs a server side component, that will be provided as a service by Screenz in order to create the app in the server, which will be referenced by an id in the framework.

In order to make your own Screenz client we will guide you through the following steps:
  - Screenz Framework
  - Application configuration file
  - Basic initialization code

#### Adding the Screenz Framework

First of all create the single view application in Xcode. 

**Important:** the framework requires iOS 8.0+, so remember to set "Deployment Target" to 8.0 or higher.

#### Adding the application configuration file

### [CocoaPods](https://github.com/CocoaPods/CocoaPods)
Add the following line in your `Podfile`.
```
pod "ScreenzSDK"
```

The framework uses a JSON configuration file in order to implement the different client functionalities and to send it to the server. This configuration file looks similar to the following:

```sh
{
    "pids": [<your application id>],
    "dev_env" : false,
    "useOnPageLoaded" : true,
    "social": {
        <social networks configurations>
    },
    "os": {
        "ios": {
            <platform specifics configuration>
        }
    },
    "glossary": {
        <glossary terms>
    }
}
```

We will discuss every item in the configuration file later, but in order to integrate this in the client you just need to add the file to the project like any other file.

#### Adding camera, mic, library and location permissions

Need to add the following keys with the desired value to be shown to the user in the app Info.plist

```xml

<key>NSCameraUsageDescription</key>
<string>Camera</string>
<key>NSLocationUsageDescription</key>
<string></string>
<key>NSLocationWhenInUseUsageDescription</key>
<string></string>
<key>NSMicrophoneUsageDescription</key>
<string>Microphone</string>
<key>NSPhotoLibraryUsageDescription</key>
<string>Photos</string>

```

#### Framework configuration code

Go to your AppDelegate.h file and replace the code with

```objective-c
#import <UIKit/UIKit.h>

@class ScreenzSDKLoadingViewController;

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;

@property (strong, nonatomic) ScreenzSDKLoadingViewController *viewController;

@end
```
Basically we just defined the View Controller that will handle all the flow of the app, the ScreenzSDKLoadingViewController.

Now, you AppDelegate.m should look something like the following (copy and replace your current code)

```objective-c
#import "AppDelegate.h"
#import <ScreenzSDK/ScreenzSDK.h>

@interface AppDelegate ()

@end

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];

    //Initialize the SDK Manager shared instance
    ScreenzSDKManager* manager = [ScreenzSDKManager sharedInstance];
    [manager loadConfigurationFromJSONFile:@"cn-data-dev"];
    /////

    //Set the view controller
    self.viewController = [[ScreenzSDKLoadingViewController alloc] initVC];
    self.window.rootViewController = self.viewController;
    [self.window makeKeyAndVisible];

    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo fetchCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler {
    [[ScreenzSDKManager sharedInstance] receiveRemoteNotificationWithData:userInfo
                                                         applicationState:application.applicationState
                                                        completionHandler:completionHandler];
}

- (void)application:(UIApplication *)application didRegisterUserNotificationSettings:(UIUserNotificationSettings *)notificationSettings {
    if (notificationSettings.types == UIUserNotificationTypeNone)
        [[ScreenzSDKManager sharedInstance] registerUserNotification];
    else
        [[UIApplication sharedApplication] registerForRemoteNotifications];
}

- (void) application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {
    [[ScreenzSDKManager sharedInstance] registerForRemoteNotificationsWithToken:deviceToken];
}

- (void)application:(UIApplication*)application didFailToRegisterForRemoteNotificationsWithError:(NSError*)error {
    [[ScreenzSDKManager sharedInstance] failtRegisterForRemoteNotifications];
}

- (BOOL)application: (UIApplication *)application openURL: (NSURL *)url sourceApplication: (NSString *)sourceApplication annotation: (id)annotation {
    return [[ScreenzSDKManager sharedInstance] processApplicaitonOpenURL:url sourceApplication:sourceApplication annotation:annotation configurationFile:JSON_DATA];
}

-(BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options {
    return [[ScreenzSDKManager sharedInstance] processApplicaitonOpenURL:url options:options configurationFile:JSON_DATA];
}

@end
```

In the 'application:didFinishLaunchingWithOptions:' we made two changes. First of all (and always should be the first thing to do) initialize the SDK with your configuration file. Your entry point for the SDK will be the ScreenzSDKManager instance, this will be always your way to communicate with the framework. As you can see we use the sharedInstance of this object but you can create and maintain your own instances if needed.
The loadConfigurationFromJSONFile takes the name of the JSON file (must end with .json), reads it and configures the framework.

After configuring the framework we need to give control over the app to the SDK. To do that we just set the ScreenzSDKLoadingViewController as the rootViewController of our app.

These two basic steps are the core of the Screenz Framework and should be done always in the exact same secuence as explained.

The following changes should let the framework handle push notifications from the server and launch the app externally.

For notifications, just change the following callbacks

```objective-c
- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo fetchCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler {
    [[ScreenzSDKManager sharedInstance] receiveRemoteNotificationWithData:userInfo
                                                         applicationState:application.applicationState
                                                        completionHandler:completionHandler];
}

- (void)application:(UIApplication *)application didRegisterUserNotificationSettings:(UIUserNotificationSettings *)notificationSettings {
    if (notificationSettings.types == UIUserNotificationTypeNone)
        [[ScreenzSDKManager sharedInstance] registerUserNotification];
    else
        [[UIApplication sharedApplication] registerForRemoteNotifications];
}

- (void) application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {
    [[ScreenzSDKManager sharedInstance] registerForRemoteNotificationsWithToken:deviceToken];
}

- (void)application:(UIApplication*)application didFailToRegisterForRemoteNotificationsWithError:(NSError*)error {
    [[ScreenzSDKManager sharedInstance] failtRegisterForRemoteNotifications];
}
```

And for launching app externally, apply the following callback:

```objective-c
- (BOOL)application: (UIApplication *)application openURL: (NSURL *)url sourceApplication: (NSString *)sourceApplication annotation: (id)annotation {
    return [[ScreenzSDKManager sharedInstance] processApplicaitonOpenURL:url sourceApplication:sourceApplication annotation:annotation configurationFile:JSON_DATA];
}

-(BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options {
    return [[ScreenzSDKManager sharedInstance] processApplicaitonOpenURL:url options:options configurationFile:JSON_DATA];
}
```

After these 3 steps, the application is ready to run. Enjoy!

#### Sending Data to the webview

You can send any data that the webview needs to consume using the following method:
 
```objective-c
[manager setExtraData:@"data to store"];
```

In this example, the webview will have access to "data to store" when is run.
This data needs to be set before launching the framework

You can also set the page to be opened and pid with these methods:

```objective-c
[manager setLaunchPageID:@"[PAGEID]"];
[manager changeCurrentPID:PID];
```

## Application Configuration File

This JSON file is the one used to configure all  client and server aspects of the framework. The entire JSON file should look something like this

```sh
{
    "pid": <your application id>,
    "dev_env" : false,
    "useOnPageLoaded" : true,
    "video_upload_key" : <your video upload api key>,
    "social": {
        "facebook": {
            "appID": "<fb appid>",
            "secret": "<fb secret>",
            "appName": "<fb app name>"
        },
        "twitter": {
            "key": "<tw key>",
            "secret": "<tw secret>"
        },
        "google": {
            "clientID": "<google id>.apps.googleusercontent.com"
        }
    },
    "os": {
        "ios": {
            "app_status_bar_hidden":true,
            "notifications_enabled":true,
            "web_data_mode":"production"
        }
    },
    "glossary": {
        "noConnectionError": "Please check your internet connection"
    }
}
```

**pid:** *[Integer, Required]* Application ID that identifies your application on the server backend.

**dev_env:** *[Boolean, Optional]* Specifies if we are using the development enviroment or not, mostly using during development and should probably be set to false (default value if not present).

**useOnPageLoaded:** *[Boolean, Optional]* This should be referred to by the server, it set to true the application shall fire this callback (false by default).

**social:** *[Array, Optional]* Enumerates the configuration for the different social networks supported by the framework. Supported networks: Facebook, Twitter, Google Plus.

**os.ios:** *[Array, Optional]* Platform specific features:
  - app_status_bar_hidden *[Boolean]*: App status bar hidden yes/no
  - notifications_enabled *[Boolean]*: Notifications enables yes/no
  - web_data_mode *[String]*: Data mode from server, should probably always use "production"

**glossary:** *[Array, Optional]* Glossary of terms used in the app that can be configured by the client. Currently only supports the "noConnectionError" message.

**video_upload_key:** *[String, Optional]* API Key for the upload video service (like cameraTag API key).

## Screenz SDK Components

### Screenz SDK Manager
This component provides a unified entry point for the framework and handles the configuration and initialization of the framework.

It's built to provide all the functionality for the framework and provide options to use it as a shared instance across the entire application, or to create multiple instances to handle independently.

The main methods for this class are responsible to load the application configuration to the SDK. These methods are *loadConfigurationFromJSONFile* and *loadConfigurationFromJSONString*. Both methods do the same, load the *appConfiguration* property based on a JSON file or string.

This component also provides the methods to handle notifications and application launch.

Besides these methods, the manager stores data to be used during the life of the application. It stores the application and the server configuration (*serverData*), SDK configuration (*sdkConfiguration*) and scheme values (*schemeValues*).

### Screenz SDK Loading View Controller

This component is responsible to start the application and load the application content. Bascially it sets the splash screen, loads the data from the server to the SDK manager, sets up the notifications and all the social networks and gets current location. After setup is complete, it will show the Main View where the web app is loaded.

### Screenz SDK Storage Keys

During the app lifecycle, the SDK stores some data in the User Configuration settings. These are the keys in the User Configuration settings that you can access if needed.

| Key Name | Description |
|--- | --- |
| **kSSDK_LOCAL_CONFIG_PID** | appId configured in the Application Configuration |
| **kSSDK_LOCAL_CONFIG_isQA** | QA mode enabled or not |
| **kSSDK_LOCAL_CONFIG_PushPageId** | pageId received in notifications |
| **kSSDK_LOCAL_CONFIG_MsgId** | msgId received in notifications |
| **kSSDK_LOCAL_CONFIG_UDID** | udid of the current phone |
| **kSSDK_LOCAL_CONFIG_GPlusId** | Google plus client id |
| **kSSDK_LOCAL_CONFIG_TWid** | Twiter key |
| **kSSDK_LOCAL_CONFIG_INSid** | Instagram client id |
| **kSSDK_LOCAL_CONFIG_FBid** | Facebook app id |
