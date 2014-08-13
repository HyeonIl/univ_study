//
//  SecondViewController.h
//  NDDN
//
//  Created by 동아 on 14. 6. 7..
//  Copyright (c) 2014년 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AppDelegate.h"

@interface SecondViewController : UIViewController
{
    UIImage *leftUpImg, *rightUpImg, *allUpImg, *allDnImg;
    UIImage *Img_1,*Img_2,*Img_3;
    
    AppDelegate *appData;
    
    IBOutlet UIImageView *ppororoView;
    IBOutlet UIImageView *countdown;
    IBOutlet UIProgressView *threadProgressView;
    IBOutlet UILabel *scoreLabel;
    
    //버튼 IBOutlet
    IBOutlet UIButton *blueUpbtn;
    IBOutlet UIButton *blueDnbtn;
    IBOutlet UIButton *whiteUpbtn;
    IBOutlet UIButton *whiteDnbtn;
    
    BOOL btnEn;
    
    int quizCnt;

    int testScore;
}

-(IBAction)nextPage;

@property (strong, nonatomic) IBOutlet UILabel *Que,*inp;
-(IBAction)pause;
-(IBAction)make_que;
-(IBAction)blue_up;
-(IBAction)blue_down;
-(IBAction)white_up;
-(IBAction)white_down;
-(void)check_OK;
-(void)now_OX;
-(void)animation;
-(void)btnEnable;

//test
-(void)makeMyProgressBarMoving;

@end
