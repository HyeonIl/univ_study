//
//  ViewController.h
//  simGame22
//
//  Created by jangdo on 14. 4. 10..
//  Copyright (c) 2014년 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Character.h"
#import "Player.h"
#import "Monster.h"

@class Character,Player,Monster;
@interface ViewController : UIViewController
{
    Player* player;
    Monster* monster;
    int monNum;
}


@property (strong,nonatomic) IBOutlet UITextField *playerNamefield;
@property (strong,nonatomic) IBOutlet UILabel *playerHP;
@property (strong,nonatomic) IBOutlet UILabel *playerMAXHP;
@property (strong,nonatomic) IBOutlet UILabel *playerAttack;
@property (strong,nonatomic) IBOutlet UILabel *playerMoney;

@property (strong,nonatomic) IBOutlet UITextField *monsterNamefield;
@property (strong,nonatomic) IBOutlet UILabel *monsterHP;
@property (strong,nonatomic) IBOutlet UILabel *monsterMAXHP;
@property (strong,nonatomic) IBOutlet UILabel *monsterAttack;
@property (strong,nonatomic) IBOutlet UILabel *monsterItem;
@property (strong,nonatomic) IBOutlet UIButton *userAtkBtn;

@property (strong,nonatomic) IBOutlet UILabel *pstat;
@property (strong,nonatomic) IBOutlet UILabel *status;


-(IBAction)playerAttackk;
-(IBAction)monsterAtttack;
-(IBAction)playerHeal;
-(IBAction)createMonster;

@end
