//
//  Character.h
//  simGame22
//
//  Created by jangdo on 14. 4. 10..
//  Copyright (c) 2014년 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Character : NSObject


@property (strong,nonatomic) NSString *cname;
@property NSInteger chp;
@property NSInteger catkP;
@property NSInteger cMaxHP;
@property Boolean deadChk;

-(void)initWithHp:(NSInteger)hp WithAttack:(NSInteger) ap WithName:(NSString*)name;

@end
