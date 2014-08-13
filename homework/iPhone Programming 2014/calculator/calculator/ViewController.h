//
//  ViewController.h
//  calculator
//
//  Created by 동아 on 14. 5. 2..
//  Copyright (c) 2014년 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController
{
    int totalResult;
    int curData;
    bool operCheck;
    NSString *lastChar;
    NSString *preOper;
}

@property (nonatomic,strong) IBOutlet UILabel *totalLabel;
@property (nonatomic,strong) IBOutlet UILabel *currentLabel;
@property (nonatomic,strong) IBOutlet UISwitch *statSwitch;
@property (nonatomic,strong) IBOutlet UISlider *fontChanger;



-(IBAction)numberTouch:(id)sender;
-(IBAction)operTouch:(id)sender;
-(IBAction)changeFont;
-(IBAction)ClearData;

@end
