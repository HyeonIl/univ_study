//
//  Character.m
//  simGame22
//
//  Created by jangdo on 14. 4. 10..
//  Copyright (c) 2014년 __MyCompanyName__. All rights reserved.
//

#import "Character.h"

@implementation Character

@synthesize cname,chp,catkP,cMaxHP,deadChk;


//각각의 입력값을 받아서 Character클래스 포함 상속받는 모든 클래스의 초기값 정해주는 메소드
-(void)initWithHp:(NSInteger)hp WithAttack:(NSInteger) ap WithName:(NSString*)name{

    cname = name;
    chp = hp;
    catkP = ap;
    cMaxHP = hp;
    deadChk = FALSE;
}

@end
