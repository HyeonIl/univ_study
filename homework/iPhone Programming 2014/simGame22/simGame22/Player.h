//
//  Player.h
//  simGame22
//
//  Created by jangdo on 14. 4. 10..
//  Copyright (c) 2014년 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Character.h"
#import "Monster.h"

@class Monster;
@interface Player : Character

@property NSInteger money;

-(void)attack:(Player*)user WithMonster:(Monster*)mob;

@end
