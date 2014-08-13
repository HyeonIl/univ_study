//
//  ViewController.m
//  NDDN
//
//  Created by 동아 on 14. 6. 7..
//  Copyright (c) 2014년 __MyCompanyName__. All rights reserved.
//

#import "ViewController.h"
#import "ScoreListView.h"
#import "AppDelegate.h"
#import "LoadingViewController.h"

@implementation ViewController
@synthesize sharedArray;

-(IBAction)startGame
{
    //네비게이션컨트롤러를 이용하여 화면이동 구현
    
    LoadingViewController *loadViewController = [[LoadingViewController alloc]initWithNibName:@"LoadingViewController" bundle:nil];
    
    [self.navigationController pushViewController:loadViewController animated:YES];
}


-(IBAction)movdScoreView
{
    //네비게이션컨트롤러를 이용하여서
    //ScoreView를 push해주면서 화면 이동
    ScoreListView *scoreView = [[ScoreListView alloc]initWithNibName:@"ScoreListView" bundle:nil];
    
    [self.navigationController pushViewController:scoreView animated:YES];
}



- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (void)viewWillAppear:(BOOL)animated
{
    
    
    //화면이 보여질때 네비게이션 바를 숨겨준다.
    
    [self.navigationController setNavigationBarHidden:YES animated:animated];
    
    
    
    [super viewWillAppear:animated];
    
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
}

@end
