//
//  ThirdViewController.h
//  NDDN
//
//  Created by 동아 on 14. 6. 7..
//  Copyright (c) 2014년 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ScoreListView.h"
#import "ViewController.h"

@interface ThirdViewController : UIViewController
{
    NSNumber *testData;
    NSString *testStr;
    NSMutableArray *scoreArray;
    
    IBOutlet UILabel *scoreLabel;
}

@end
