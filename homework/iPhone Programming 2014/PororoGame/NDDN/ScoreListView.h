//
//  ScoreListView.h
//  NDDN
//
//  Created by 동아 on 14. 6. 7..
//  Copyright (c) 2014년 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ThirdViewController.h"
#import "AppDelegate.h"

@class ThirdViewController;
@interface ScoreListView : UIViewController<UITableViewDelegate,UITableViewDataSource>
{
    AppDelegate *appData;
    IBOutlet UITableView *rankTable;
    //ThirdViewController *thirdCont;
}

@property (nonatomic,assign) NSMutableArray *rankData;


@end
