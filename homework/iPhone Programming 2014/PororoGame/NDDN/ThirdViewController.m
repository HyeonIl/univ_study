//
//  ThirdViewController.m
//  NDDN
//
//  Created by 동아 on 14. 6. 7..
//  Copyright (c) 2014년 __MyCompanyName__. All rights reserved.
//

#import "ThirdViewController.h"
#import "ViewController.h"
#import "AppDelegate.h"

@implementation ThirdViewController

-(void)moveRootPage:(id)sender{
    
    //돌아가기 버튼을 눌렀을때
    //네비게이션컨트롤러 안의 뷰들을 모두 pop해서 첫 화면을 보여준다.
    [self.navigationController popToRootViewControllerAnimated:YES];
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
    [super viewDidLoad];
    
    
    //네비게이션의 왼쪽 버튼을 커스텀 한다.
    //눌럿을때 실행되는 메소드로 moveRootPage가 되도록 정의한다.
    //현재 사용되고있는 self의 네비게이션컨트롤러의 왼쪽버튼이 커스텀시킨
    //버튼이 되도록 설정함.
    
    UIBarButtonItem *moveButton = [[UIBarButtonItem alloc]initWithTitle:@"돌아가기" style:UIBarButtonItemStylePlain target:self action:@selector(moveRootPage:)];
    self.navigationItem.leftBarButtonItem = moveButton;
    
}

- (void)viewDidUnload
{
    [super viewDidUnload];
}

-(void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    
    //AppDelegate의 데이터들을 현재 뷰에서 사용할 수 있도록 해 준다.
    AppDelegate *appData = (AppDelegate*)[[UIApplication sharedApplication]delegate];
    
    //NSLog(@"%@",appData.gameScore);
    
    //기록된 점수를  scoreLabel에 보여준다.
    scoreLabel.text = [NSString stringWithFormat:@"%@",appData.gameScore];
    
    //점수를 AppDelegate에 선언된 배열에 데이터를 추가시켜준다.
    [appData.sharedTestArray addObject:appData.gameScore];
    
    NSLog(@"%@",appData.sharedTestArray);
    
    
    /*******************************************************************************/
    //                          정렬구현부!!!!                                       //
    //랭킹이므로 내림차순 정렬한다.
    
    NSArray *sortedArray = [appData.sharedTestArray sortedArrayUsingComparator:^(id obj1, id obj2) {
        if ([obj1 integerValue] > [obj2 integerValue])
            return (NSComparisonResult)NSOrderedAscending;
        else if ([obj1 integerValue] < [obj2 integerValue] )
            return (NSComparisonResult)NSOrderedDescending;
        else
            return (NSComparisonResult)NSOrderedSame;
    }];
    
    //정렬이 완료된 배열을 다시 AppDelegate의 sortedRankArray에 넣어줌
    appData.sortedRankArray = sortedArray;
    
}


- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

@end
