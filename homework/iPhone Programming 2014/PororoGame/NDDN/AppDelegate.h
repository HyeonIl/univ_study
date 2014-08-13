//
//  AppDelegate.h
//  NDDN
//
//  Created by 동아 on 14. 6. 7..
//  Copyright (c) 2014년 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class ViewController;

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;

@property (strong, nonatomic) ViewController *viewController;


/*************************************************************/
//뷰간의 데이터 공유는 전적으로 AppDelegate에서 선언된 변수로 구현한다
//따라서 AppDelegate에 변수들을 선언함

//첫번재 배열은  MutableArray를 사용함으로 3번째 점수를 보여주는 화면에서
//점수가 한번씩 추가될 수 있게 선언한 배열
//두번째 배열은 랭킹을 구현하기 위해 첫번째 MutableArray의 배열값들을
//바탕으로 정렬하여 배열을 다시 구현한것
/*************************************************************/
@property (strong,nonatomic) NSMutableArray *sharedTestArray;
@property (strong,nonatomic) NSArray* sortedRankArray;


//게임에 해당하는 점수를 선언
@property (strong,nonatomic) NSNumber* gameScore;
//퀴즈개수
@property (strong,nonatomic) NSNumber* quizNumber;



@end
