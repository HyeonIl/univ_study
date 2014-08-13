//
//  ViewController.m
//  simGame22
//
//  Created by jangdo on 14. 4. 10..
//  Copyright (c) 2014년 __MyCompanyName__. All rights reserved.
//

#import "ViewController.h"

@implementation ViewController

@synthesize playerNamefield,monsterNamefield;
@synthesize playerAttack,playerHP,playerMAXHP;
@synthesize monsterHP,monsterAttack,monsterMAXHP;
@synthesize status,playerMoney,monsterItem,pstat;
@synthesize userAtkBtn;

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad 
{
    [super viewDidLoad];
    //메모리할당
    player = [Player alloc];
    monster = [Monster alloc];
    
    //Character클래스에 선언한 초기화 메소드로 능력치 초기화
    [monster initWithHp:150 WithAttack:10 WithName:@"오크"];
    [player initWithHp:rand()%100+100 WithAttack:rand()%100+10 WithName:@"검사"];
    
    monNum = 1;
    player.money = 0;
    monster.item = 20;
    monster.tempItem = monster.item;
    
    
    //Label에 변환된 값을 대입시켜서 업데이트 시켜줌
    playerNamefield.text = player.cname;
    playerHP.text = [NSString stringWithFormat:@"%d",player.chp];
    playerMAXHP.text = [NSString stringWithFormat:@"%d",player.cMaxHP];
    playerAttack.text = [NSString stringWithFormat:@"%d",player.catkP];
    playerMoney.text = [NSString stringWithFormat:@"%d",player.money];
    
    monsterNamefield.text = monster.cname;
    monsterHP.text = [NSString stringWithFormat:@"%d",monster.chp];
    monsterMAXHP.text = [NSString stringWithFormat:@"%d",monster.cMaxHP];
    monsterAttack.text = [NSString stringWithFormat:@"%d",monster.catkP];
    monsterItem.text = [NSString stringWithFormat:@"%d",monster.item];
    
    
    
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
    [super viewWillAppear:animated];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
	[super viewWillDisappear:animated];
}

- (void)viewDidDisappear:(BOOL)animated
{
	[super viewDidDisappear:animated];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
}

-(IBAction)playerAttackk
{
    //공격메소드 실행 및 레이블에 업뎃
    [player attack:player WithMonster:monster];
    monsterHP.text = [NSString stringWithFormat:@"%d",monster.chp];
    //몬스터가 죽었을때 돈이 올라가고 버튼이 안눌러지게 함
    if(monster.deadChk == TRUE){
        status.text = @"몬스터 Dead!!!";
        pstat.text = [NSString stringWithFormat:@"%d$획득",monster.tempItem];
        player.money += monster.item;
        monster.item = 0;
        playerMoney.text = [NSString stringWithFormat:@"%d",player.money];
        monsterItem.text = [NSString stringWithFormat:@"%d",monster.item];
        userAtkBtn.enabled = FALSE;
    }
}
-(IBAction)monsterAtttack
{
        [monster attack:player WithMonster:monster];
        playerHP.text = [NSString stringWithFormat:@"%d",player.chp];

}

-(IBAction)playerHeal
{
    //플레이어의 최대체력보다 플레이어의 현재체력이 작고 플레이어의 최대체력과 현재체력을 뺀값이 힐량 12 보다 크거나 같을때만
    //힐 실행
    if(player.cMaxHP > player.chp && (player.cMaxHP - player.chp) >= 12){
        player.chp = player.chp+12;
    //아닐때는 최대체력을 현재체력에 대입
    }else if((player.cMaxHP - player.chp) < 12){
        player.chp = player.cMaxHP;
    }
    //업뎃
        playerHP.text = [NSString stringWithFormat:@"%d",player.chp];
}

-(IBAction)createMonster
{
    NSString *mobName = [NSString stringWithFormat:@"Monster%d",monNum];
    [monster initWithHp:rand()%100+50 WithAttack:rand()%10+10 WithName:mobName];
    userAtkBtn.enabled = TRUE;
    status.text = [NSString stringWithFormat:@"Monster%d등장!!",monNum++];
    monster.item = rand()%100 + 20;
    monster.tempItem = monster.item;
    monsterNamefield.text = monster.cname;
    monsterHP.text = [NSString stringWithFormat:@"%d",monster.chp];
    monsterMAXHP.text = [NSString stringWithFormat:@"%d",monster.cMaxHP];
    monsterAttack.text = [NSString stringWithFormat:@"%d",monster.catkP];
    monsterItem.text = [NSString stringWithFormat:@"%d",monster.item];
}

@end
