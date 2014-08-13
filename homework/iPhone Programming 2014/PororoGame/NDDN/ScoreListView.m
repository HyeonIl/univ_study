//
//  ScoreListView.m
//  NDDN
//
//  Created by 동아 on 14. 6. 7..
//  Copyright (c) 2014년 __MyCompanyName__. All rights reserved.
//

#import "ScoreListView.h"
#import "AppDelegate.h"

@implementation ScoreListView
@synthesize rankData;

-(NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return appData.sortedRankArray.count;
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIndentifier = @"Cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIndentifier];
    
    NSString *numberToString;
    
    if(cell == nil)
    {
        cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:CellIndentifier];
    }
    
    //AppDelegate안의 sortedRankArray에서 가져온 데이터를
    //셀에 대입시켜준다.
    
    numberToString = [NSString stringWithFormat:@"%d등 :     %@점",
                      indexPath.row+1,
                      [appData.sortedRankArray objectAtIndex:indexPath.row]];
    
    cell.textLabel.text = numberToString;
    
    return cell;
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
    rankTable.dataSource = self;
    rankTable.delegate = self;
    
    appData = (AppDelegate*)[[UIApplication sharedApplication]delegate];
    
}

- (void)viewDidUnload
{
    [super viewDidUnload];
}

-(void)viewWillAppear:(BOOL)animated
{
    //이 화면이 보여지면 네비게이션을 보여준다
    [self.navigationController setNavigationBarHidden:NO animated:animated];
    [super viewWillAppear:animated];
}



- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

@end
