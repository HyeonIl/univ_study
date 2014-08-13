//
//  ViewController.h
//  이것이야 말로 내가 왜 하는 것일까
//
//  Created by 동아 on 14. 6. 3..
//  Copyright (c) 2014년 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
//@class Player;
@interface ViewController : UIViewController
{
    UIImage *leftUpImg, *rightUpImg, *allUpImg, *allDnImg;
    UIImage *Img_1,*Img_2,*Img_3;
    
    IBOutlet UIImageView *ppororoView;
    IBOutlet UIImageView *countdown;
}

@property (strong, nonatomic) IBOutlet UILabel *Que,*inp;
-(IBAction)make_que;
-(IBAction)blue_up;
-(IBAction)blue_down;
-(IBAction)white_up;
-(IBAction)white_down;
-(void)check_OK;
-(void)now_OX;
-(void)animation;
//@property (strong, nonatomic) IBOutlet UIProgressView * threadProgressView;
@end
