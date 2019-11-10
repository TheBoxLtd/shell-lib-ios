# Screenz SDK
## [~>4.0]

Screenz SDK allows you to implement your own Screenz client that will live in the Screenz environment.

This environment needs a server side component, that will be provided by the infraestructure department in order to create the app in the server, which will be referenced by an id in the framework.

In order to make your own Screenz client we will guide you through the following steps:
  - Screenz Framework
  - Application configuration file
  - Basic initialization code

#### Adding the Screenz Framework

First of all create the single view application in Xcode. After that you must add the ScreenzSDK.framework to the project like the following screenshot

![](http://www.mvdforge.com/images/screenz_projectConfigScreen.png)

#### Adding Build Phase Script

In order for the sdk to work correctly, it is needed to sign it at the end of the build process.
For this add the following 'Run Script' as the last step in the project build phases:

```sh
pushd "${TARGET_BUILD_DIR}"/"${PRODUCT_NAME}".app/Frameworks/ScreenzSDK.framework/Frameworks
for EACH in *.framework; do
/usr/bin/codesign --force --deep --sign "${EXPANDED_CODE_SIGN_IDENTITY}" --entitlements "${TARGET_TEMP_DIR}/${PRODUCT_NAME}.app.xcent" --timestamp=none $EACH
done
popd
echo "BUILD DIR ${TARGET_BUILD_DIR}"
```

**Important:** the framework requires iOS 9.0+, so remember to set "Deployment Target" to 9.0 or higher.

#### Adding the application configuration file

The framework use a JSON configuration file in order to implement the different functionalities based locally in the client and to send it over to the server. That configuration file looks similar to the following

```sh
{
    "pids": [<your application ids>],
    "dev_env" : false,
    "useOnPageLoaded" : true,
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

Initialize the manager with your configuration file in the ```application:didFinishLaunchingWithOptions``` callback in your AppDelagete

```objective-c
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    
    ....
    
    //Initialize the SDK Manager shared instance
    ScreenzSDKManager* manager = [ScreenzSDKManager sharedInstance];
    [manager loadConfigurationFromJSONFile:@"cn-data-dev"];
    /////

    return YES;
}
```

Also, you need to send the information to the framework in the following callbacks

```objective-c
- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo fetchCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler {
    NSLog(@"RECEIVE Remote notification %@",userInfo);
    
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
    NSLog(@"Failed to get device token, error: %@", error);
    [[ScreenzSDKManager sharedInstance] failtRegisterForRemoteNotifications];
}

- (BOOL)application: (UIApplication *)application openURL: (NSURL *)url sourceApplication: (NSString *)sourceApplication annotation: (id)annotation {
    return [[ScreenzSDKManager sharedInstance] processApplicaitonOpenURL:url sourceApplication:sourceApplication annotation:annotation configurationFile:JSON_DATA viewController:self.window.rootViewController.presentedViewController];
}

-(BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options {
    return [[ScreenzSDKManager sharedInstance] processApplicaitonOpenURL:url options:options configurationFile:JSON_DATA  viewController:self.window.rootViewController.presentedViewController];
}
```

This concludes the basic steps to configure the framework. In order to display the content of the framework you have to assign it a view in your view controller.

To show the framework you have to load it in a view. For example:

```objective-c
- (void)viewDidLoad {
    [super viewDidLoad];
    
    [[ScreenzSDKManager sharedInstance] loadInView:self.view viewController:self];
}
```

This will load the framework in the view controller using the entire space of the view controller (we set the view as the root view of the view controller).

Now the application is ready to run.

## Application Configuration File

This JSON file is the one used to configure all the client and server aspects of the framework. The entire JSON file should look something like this

```sh
{
    "pids": [<your application ids>],
    "dev_env" : false,
    "useOnPageLoaded" : true,
    "video_upload_key" : <your video upload api key>,
    "os": {
        "ios": {
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

**os.ios:** *[Array, Optional]* Platform specific features:
  - notifications_enabled *[Boolean]*: Notifications enables yes/no
  - web_data_mode *[String]*: Data mode from server, should probably always use "production"

**glossary:** *[Array, Optional]* Glossary of terms used in the app that can be configured by the client. Currently only supports the "noConnectionError" message.

**video_upload_key:** *[String, Optional]* API Key for the upload video service.

## Screenz SDK Components

We are going to explain the main components of the SDK for further understanding of the framework itself and the work under the hood in the SDK.

### Screenz SDK Manager
This manager provides an unified entry point for the framework and handle the configuration and initialization of the framework itself.

Was build to provide all the functionality for the framework and provide options to use it as a shared instance accros the entire application, or to create multiple instances to handle independently.

The main methods for this class are the one in charge of load the application configuration to the SDK, this methods are *loadConfigurationFromJSONFile* and *loadConfigurationFromJSONString*. Both methods do the same, load the *appConfiguration* property based on a JSON file or string. Also, *loadInView* is in charge of displaying the framework web view.

Also provides the methods to handle notifications and application launch.

Besides this methods, the manager store data to be used during the life of the application. As we know, it stores the application configuration but also the server configuration (*serverData*), SDK configuration (*sdkConfiguration*) and scheme values (*schemeValues*).

The Screenz SDK Manager also has a way to set a delegate in order to receive data from the web. For that, you just need to call the *setDelegate* method with an object that conform the *ScreenzSDKManagerDelegate* protocol. When the web send some data back to the app, it will be available in the *ScreenzSDKManagerDelegate_dataReceived* selector.

#### Exit SDK Event

Using the delegate described above, the webview will request to exit with the data **'sdk-exit-new'**.
You should subscribe to this event, close the sdk when received and handle the views lifecycle accordingly 

In addition to this, an optional extra call is available to cleanup any objects the sdk may be holding in memory as follows:
```objective-c
[manager clearView];
```

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
 
### Screenz SDK Storage Keys

During the life of the app, the SDK store some data in the User Configuration settings. These are the keys in the User Configuration settings that you can access if needed.

| Key Name | Description |
|--- | --- |
| **kSSDK_LOCAL_CONFIG_PID** | appId configured in the Application Configuration |
| **kSSDK_LOCAL_CONFIG_isQA** | QA mode enabled or not |
| **kSSDK_LOCAL_CONFIG_PushPageId** | pageId received in notifications |
| **kSSDK_LOCAL_CONFIG_MsgId** | msgId received in notifications |
| **kSSDK_LOCAL_CONFIG_UDID** | udid of the current phone |





