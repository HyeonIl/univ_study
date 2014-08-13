//
//  LoadingViewController.h
//  NDDN
//
//  Created by 동아 on 14. 6. 19..
//  Copyright (c) 2014년 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AppDelegate.h"

@interface LoadingViewController : UIViewController
{
    IBOutlet UIImageView *loadView;
    AppDelegate *appDelgate;
    
    IBOutlet UITextField *inputTF;
    IBOutlet UIButton *quizBtn;
    IBOutlet UILabel *quizLabel;
    
    UIImage *img_3;
    UIImage *img_2;
    UIImage *img_1;
    UIImage *img_GO;
}

-(void)loadingAnimation;

@end
