//
//  Player.m
//  simGame22
//
//  Created by jangdo on 14. 4. 10..
//  Copyright (c) 2014년 __MyCompanyName__. All rights reserved.
//

#import "Player.h"

@implementation Player

@synthesize money;

//Attack메소드 구현
//Monster클래스와 User클래스를 매개변수로 받아와서 플레이어의 공격력 만큼 몬스터의 체력이 깎인다
-(void)attack:(Player*)user WithMonster:(Monster*)mob{
    
    //몬스터의 체력이 0보다 크고 플레이어의 공격보다 남은 체력이 클때만 체력이 깎이게 한다
    if(mob.chp > 0 && mob.chp > user.catkP){
     mob.chp -= user.catkP;
    //몬스터의 체력보다 플레이어의 공격력이 작거나 같을때 몬스터의 체력을 0으로 만들어줌
    }else if(mob.chp <= user.catkP){
        mob.chp = 0;
    }
    //몬스터의 체력이 0이 되면 죽었다는 bool값을 TRUE로 만들어줌
    if(mob.chp == 0)
        mob.deadChk = TRUE;
}

@end
