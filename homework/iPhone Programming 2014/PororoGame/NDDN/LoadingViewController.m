//
//  LoadingViewController.m
//  NDDN
//
//  Created by 동아 on 14. 6. 19..
//  Copyright (c) 2014년 __MyCompanyName__. All rights reserved.
//

#import "LoadingViewController.h"
#import "SecondViewController.h"


@implementation LoadingViewController

-(IBAction)quizNumber
{
    appDelgate.quizNumber = [NSNumber numberWithInt:[inputTF.text intValue]];
    
    //2번째 뷰에서 확인 버튼을 누르면
    //"문제수를 입력하시오" <== 이 레이블
    //확인 버튼, 입력 TextField 다 안보이게 hidden처리함
    inputTF.hidden = YES;
    quizBtn.hidden = YES;
    quizLabel.hidden = YES;
    
    
    //타이머 및 애니메이션 사용으로 로딩효과 구현함.
    [NSTimer scheduledTimerWithTimeInterval:4 target:self selector:@selector(nextPage)userInfo:nil repeats:NO];
    [self loadingAnimation];
    
    [inputTF resignFirstResponder];
}

-(void)loadingAnimation
{
    
    //4개의 이미지로 애니메이션을 통하여 로딩 효과를 구현함.
    img_3 = [UIImage imageNamed:@"load3.png"];
    img_2 = [UIImage imageNamed:@"load2.png"];
    img_1= [UIImage imageNamed:@"load1.png"];
    img_GO = [UIImage imageNamed:@"start.png"];
    
    
    NSArray *imgarray = [NSArray arrayWithObjects:img_3,img_2,img_1,img_GO,nil];
    loadView.animationImages = imgarray;
    loadView.animationDuration = 4;
    loadView.animationRepeatCount = 1;
    
    [loadView startAnimating];
}


-(void)nextPage
{
    SecondViewController *secViewController = [[SecondViewController alloc]initWithNibName:@"SecondViewController" bundle:nil];
    [self.navigationController pushViewController:secViewController animated:YES];
}



- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    
    //AppDelegate의 데이터를 가져오는 메소드

    appDelgate = (AppDelegate*)[[UIApplication sharedApplication]delegate];
    
    
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

@end
