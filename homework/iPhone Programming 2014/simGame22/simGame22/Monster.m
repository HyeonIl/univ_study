//
//  Monster.m
//  simGame22
//
//  Created by jangdo on 14. 4. 10..
//  Copyright (c) 2014년 __MyCompanyName__. All rights reserved.
//

#import "Monster.h"

@implementation Monster

@synthesize item,tempItem;

-(void)attack:(Player*)user WithMonster:(Monster*)mob{
    
    if(user.chp > 0 && user.chp > mob.catkP){
        user.chp -= mob.catkP;
    }else if(user.chp <= mob.catkP){
        user.chp = 0;
    }
}

@end
