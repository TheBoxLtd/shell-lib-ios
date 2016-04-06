# Screenz SDK

Screenz SDK allows you to implement your own Screenz client that will live in the Screenz environment.

This environment needs a server side component, that will be provided by the infraestructure department in order to create the app in the server, which will be referenced by an id in the framework.

In order to make your own Screenz client we will guide you through the following steps:
  - Screenz Framework
  - Application configuration file
  - Basic initialization code

#### Adding the Screenz Framework

First of all create the single view application in Xcode. After that you must add the ScreenzSDK.framework to the project like the following screenshot

![](http://www.mvdforge.com/images/screenz_projectConfigScreen.png)

**Important:** the framework requires iOS 8.0+, so remember to set "Deployment Target" to 8.0 or higher.

#### Adding the application configuration file

The framework use a JSON configuration file in order to implement the different functionalities based locally in the client and to send it over to the server. That configuration file looks similar to the following

```sh
{
    "pid": <your application id>,
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

We will discuss every item in the configuration file later, but in order to integrate this on the client you just need to add the file to the project like any other file.

#### Framework configuration code

At this point your project should look something like this

![](http://www.mvdforge.com/images/screenz_fullProjectView.png)

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

@end
```

In the 'application:didFinishLaunchingWithOptions:' we made two changes. First of all (and always should be the first thing to do) initialize the SDK with your configuration file. Your entry point for the SDK will be the ScreenzSDKManager instance, this will be always your way to communicate with the framework. As you can see we use the sharedInstance of this object but you can create and maintain your own instances if needed.
The loadConfigurationFromJSONFile just do that, take the name of the JSON file (must end with .json), read it and configure the framework.

After configuring the framework we need to give control over the app to the SDK. To do that we just set the ScreenzSDKLoadingViewController as the rootViewController of our app.

This two basic steps are the core of the Screenz Framework and should be done always in the exact same secuence as explained.

There were a couple more changes done, which basically were let the framework handle push notifications from the server and external opening of the app.

For notifications we just changed the following callbacks

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

And for handling app openings the following callback

```objective-c
- (BOOL)application: (UIApplication *)application openURL: (NSURL *)url sourceApplication: (NSString *)sourceApplication annotation: (id)annotation {
    return [[ScreenzSDKManager sharedInstance] processApplicaitonOpenURL:url sourceApplication:sourceApplication annotation:annotation configurationFile:JSON_DATA];
}
```

After this 3 steps, the application is ready to run. Enjoy!

## Application Configuration File

This JSON file is the one used to configure all the client and server aspects of the framework. The entire JSON file should look something like this

```sh
{
    "pid": <your application id>,
    "dev_env" : false,
    "useOnPageLoaded" : true,
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
        },
        "instagram": {
            "clientID": "<ins id>",
            "secret": "<ins secret>",
            "redirectUri" : "<ins redirect url>"
        },
        "disney": {
            "disney_clientId": "<disney id>",
            "disney_environment": "<environment>"
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

**useOnPageLoaded:** *[Boolean, Optional]* This should be refered by the server, it set if the webapp supports this callback or not (false by default).

**social:** *[Array, Optional]* Enumerates the configuration for the different social networks supported by the framework. Supported networks: Facebook, Twitter, Instagram, Google and Disney.

**os.ios:** *[Array, Optional]* Platform specific features:
  - app_status_bar_hidden *[Boolean]*: App status bar hidden yes/no
  - notifications_enabled *[Boolean]*: Notifications enables yes/no
  - web_data_mode *[String]*: Data mode from server, should probably always use "production"

**glossary:** *[Array, Optional]* Glossary of terms used in the app that can be configured by the client. Currently only supports the "noConnectionError" message.

## Screenz SDK Components

We are going to explain the main components of the SDK for further understanding of the framework itself and the work under the hood in the SDK.

### Screenz SDK Manager
This manager provides an unified entry point for the framework and handle the configuration and initialization of the framework itself.

Was build to provide all the functionality for the framework and provide options to use it as a shared instance accros the entire application, or to create multiple instances to handle independently.

The main methods for this class are the one in charge of load the application configuration to the SDK, this methos are *loadConfigurationFromJSONFile* and *loadConfigurationFromJSONString*. Both methods do the same, load the *appConfiguration* property based on a JSON file or string. 

Also provides the methods to handle notifications and application launch.

Besides this methods, the manager store data to be used during the life of the application. As we know, it stores the application configuration but also the server configuration (*serverData*), SDK configuration (*sdkConfiguration*) and scheme values (*schemeValues*).
 
### Screenz SDK Loading View Controller

The Loading VC is in charge of start the application and load the web application. Bascially it set the splash screen, load the data from the server to the SDK manager, setup the notifications and all the social networks and get current location. After all this setup is done, it will show the Main VC where the web app is loaded.

### Screenz SDK Storage Keys

During the life of the app, the SDK store some data in the User Configuration settings. These are the keys in the User Configuration settings that you can access if needed.

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
| **kSSDK_LOCAL_CONFIG_Did** | Disney client id |





