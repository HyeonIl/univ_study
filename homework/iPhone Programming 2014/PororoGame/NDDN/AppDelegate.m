//
//  AppDelegate.m
//  NDDN
//
//  Created by 동아 on 14. 6. 7..
//  Copyright (c) 2014년 __MyCompanyName__. All rights reserved.
//

#import "AppDelegate.h"

#import "ViewController.h"

@implementation AppDelegate

@synthesize sharedTestArray;
@synthesize sortedRankArray;
@synthesize gameScore;
@synthesize quizNumber;
@synthesize window = _window;
@synthesize viewController = _viewController;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    // Override point for customization after application launch.
    self.viewController = [[ViewController alloc] initWithNibName:@"ViewController" bundle:nil];
    
    //네비게이션컨트롤러 등장시키는 부분
    
    UINavigationController *navigationController = [[UINavigationController alloc]initWithRootViewController:self.viewController];
    
    self.window.rootViewController = navigationController;
    
    
    //배열 초기화
    
    sharedTestArray = [NSMutableArray arrayWithObjects:nil];
    sortedRankArray = [NSArray arrayWithObjects:nil];
    
    [self.window makeKeyAndVisible];
    return YES;
}



- (void)applicationWillResignActive:(UIApplication *)application
{
   
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{

}

- (void)applicationDidBecomeActive:(UIApplication *)application
{

}

- (void)applicationWillTerminate:(UIApplication *)application
{

}

@end
