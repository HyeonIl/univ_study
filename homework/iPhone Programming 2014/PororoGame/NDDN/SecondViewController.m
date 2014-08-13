//
//  SecondViewController.m
//  NDDN
//
//  Created by 동아 on 14. 6. 7..
//  Copyright (c) 2014년 __MyCompanyName__. All rights reserved.
//

#import "SecondViewController.h"
#import "ThirdViewController.h"

@implementation SecondViewController
@synthesize Que,inp;

// 0 내린상태
// 1 올린상태
int Player_blue=0,Player_white=0;
int num=3;// 몇번 문제인제 체크 
int flog = 0; //건들이지마 타이머할때 쓰는거야 


-(void)btnEnable
{
    blueUpbtn.enabled = btnEn;
    blueDnbtn.enabled = btnEn;
    whiteUpbtn.enabled = btnEn;
    whiteDnbtn.enabled = btnEn;
}

-(IBAction)nextPage{
    ThirdViewController *thirdViewController = [[ThirdViewController alloc]initWithNibName:@"ThirdViewController" bundle:nil];
    
    [self.navigationController pushViewController:thirdViewController animated:YES];
}


-(void)animation{
    
    if(threadProgressView.progress == 1){
        [self nextPage];
    }
    
    Img_1 = [UIImage imageNamed:@"11.png"];
    Img_2 = [UIImage imageNamed:@"22.png"];
    Img_3 = [UIImage imageNamed:@"33.png"];
    
    NSArray *imgarray = [NSArray arrayWithObjects:Img_3,Img_2,Img_1,nil];
    countdown.animationImages = imgarray;
    countdown.animationDuration = 3;
    countdown.animationRepeatCount = 1;
    [countdown startAnimating];
    
    
}
-(void)now_OX      //현재 맞았는지 틀렸는지 확인 하는것. 
{
    if(flog==0)
    {
        if(num == 3 && (Player_blue != 0 || Player_white !=0)) {
            Que.text = [NSString stringWithFormat:@"틀렸습니다 "];
            btnEn = NO;
            [self btnEnable];
            //[NSTimer scheduledTimerWithTimeInterval:1.5 target:self selector:@selector(make_que) userInfo:nil repeats:NO];
        }
        else if(num == 0 && (Player_blue != 1 || Player_white !=1)){
            Que.text = [NSString stringWithFormat:@"틀렸습니다 "];
            btnEn = NO;
            [self btnEnable];
            //[NSTimer scheduledTimerWithTimeInterval:1.5 target:self selector:@selector(make_que) userInfo:nil repeats:NO];
        }
        else if(num == 1 && (Player_blue != 1 || Player_white !=0)){
            Que.text = [NSString stringWithFormat:@"틀렸습니다 "];
            btnEn = NO;
            [self btnEnable];
            //[NSTimer scheduledTimerWithTimeInterval:1.5 target:self selector:@selector(make_que) userInfo:nil repeats:NO];
        }
        else if(num == 2 && (Player_blue != 0 || Player_white !=1)){
            Que.text = [NSString stringWithFormat:@"틀렸습니다 "];
            btnEn = NO;
            [self btnEnable];
            //[NSTimer scheduledTimerWithTimeInterval:1.5 target:self selector:@selector(make_que) userInfo:nil repeats:NO];
        }
    }
}

-(void)change   //현재 뽀로로의 상황을 이미지 뷰에 표현
{
    allDnImg = [UIImage imageNamed:@"LRDown.png"];
    allUpImg = [UIImage imageNamed:@"AllUp.png"];
    rightUpImg = [UIImage imageNamed:@"RightUp.png"];
    leftUpImg = [UIImage imageNamed:@"LeftUp.png"];
    if(Player_blue == 0 && Player_white ==0)
        ppororoView.image = allDnImg;
    else if(Player_blue == 1 && Player_white ==0)
        ppororoView.image = leftUpImg;
    else if(Player_blue == 0 && Player_white ==1)
        ppororoView.image = rightUpImg;
    else if(Player_blue == 1 && Player_white ==1)
        ppororoView.image = allUpImg;
    
}
-(void)check_OK  //현재 정답인지 아닌지 체크
{
    
    if (num==0&&Player_blue==1&&Player_white==1) {
        Que.text = [NSString stringWithFormat:@"정답입니다."];
        btnEn = NO;
        [self btnEnable];
        //[NSTimer scheduledTimerWithTimeInterval:1.5 target:self selector:@selector(make_que) userInfo:nil repeats:NO];
        testScore += (100/[appData.quizNumber intValue]);
        flog=1;
    }
    else if (num==1&&Player_blue==1&&Player_white==0){
        Que.text = [NSString stringWithFormat:@"정답입니다."];
        btnEn = NO;
        [self btnEnable];
        //[NSTimer scheduledTimerWithTimeInterval:1.5 target:self selector:@selector(make_que) userInfo:nil repeats:NO];
        testScore += (100/[appData.quizNumber intValue]);
        flog=1;
    }
    else if (num==2&&Player_blue==0&&Player_white==1){
        Que.text = [NSString stringWithFormat:@"정답입니다."];
        btnEn = NO;
        [self btnEnable];
        //[NSTimer scheduledTimerWithTimeInterval:1.5 target:self selector:@selector(make_que) userInfo:nil repeats:NO];
        testScore += (100/[appData.quizNumber intValue]);
        flog=1;
    }
    else if (num==3&&Player_blue==0&&Player_white==0){
        Que.text = [NSString stringWithFormat:@"정답입니다."];
        btnEn = NO;
        [self btnEnable];
        //[NSTimer scheduledTimerWithTimeInterval:1.5 target:self selector:@selector(make_que) userInfo:nil repeats:NO];
        testScore += (100/[appData.quizNumber intValue]);
        flog=1;
    }
    
    scoreLabel.text = [NSString stringWithFormat:@"%d",testScore];
    NSLog(@"현재점수 : %d점",testScore);
    
    
}
-(IBAction)make_que   
{
    btnEn = YES;
    [self btnEnable];
    
    if(quizCnt !=0){
        int tmp = num;   //  똑같은 문제가 나오지 않도록 조건 걸었뒹
        for(;;)
        {
            num = arc4random()%4;//1부터 4까지
            if(tmp != num)
            {
                if(num == 3 && (Player_blue != 0 || Player_white !=0)) 
                    break;
                else if(num == 0 && (Player_blue != 1 || Player_white !=1))
                    break;
                else if(num == 1 && (Player_blue != 1 || Player_white !=0))
                    break;
                else if(num == 2 && (Player_blue != 0 || Player_white !=1))
                    break;
            }
        }
    flog =0;
    [self animation];
    NSArray *arr = [[NSArray alloc]initWithObjects:@"청기올려 백기올려",@"청기올려 백기내려",@"청기내려 백기올려",@"청기내려 백기내려", nil];
    
    
    
    Que.text = [NSString stringWithFormat:@"%@",[arr objectAtIndex:num]]; 
        
    quizCnt--;
    
    [NSTimer scheduledTimerWithTimeInterval:3 target:self selector:@selector (now_OX)userInfo:nil repeats:NO];
    [NSTimer scheduledTimerWithTimeInterval:4.5 target:self selector:@selector (make_que)userInfo:nil repeats:NO];
        
        
    //프로그레시시브의 value값을 현재 입력된 문제의 숫자에 1 로 나누어주어서
    //퍼센트를 고려하도록 함.
        
    threadProgressView.progress += (1/[appData.quizNumber floatValue]);
        
        
    }
}
-(IBAction)blue_up
{
    if(Player_blue == 0&& num!=2&num!=3){ // 청기 내린 상태이면 올리도록
        Player_blue = 1; 
        [self check_OK];
        [self change];
    }
    else{
        Que.text = [NSString stringWithFormat:@"틀렸습니다"];
        btnEn = NO;
        [self btnEnable];
        //[NSTimer scheduledTimerWithTimeInterval:1.5 target:self selector:@selector(make_que) userInfo:nil repeats:NO];
        Player_blue =0;
        Player_white=0;
        flog =1;
    }
    
}

-(IBAction)blue_down
{
    if(Player_blue == 1&& num!=0&&num!=1){ // 청기 올린 상태이면 내리도록
        Player_blue = 0; 
        [self check_OK];
        [self change];
    }
    else
    {
        Que.text = [NSString stringWithFormat:@"틀렸습니다"];
        btnEn = NO;
        [self btnEnable];
        //[NSTimer scheduledTimerWithTimeInterval:1.5 target:self selector:@selector(make_que) userInfo:nil repeats:NO];
        Player_blue =0;
        Player_white=0;
        flog =1;
    }
    
}

-(IBAction)white_up
{
    if(Player_white == 0&& num!=1&&num!=3){ // 백기 내린 상태이면 올리도록
        Player_white = 1; 
        [self check_OK];
        [self change];
    }
    
    else{
        Que.text = [NSString stringWithFormat:@"틀렸습니다"];
        btnEn = NO;
        [self btnEnable];
        //[NSTimer scheduledTimerWithTimeInterval:1.5 target:self selector:@selector(make_que) userInfo:nil repeats:NO];
        Player_blue =0;
        Player_white=0;
        flog =1;
    }
    
    
    
}

-(IBAction)white_down
{
    if(Player_white == 1&& num!=0&&num!=2){ // 백기 올린 상태이면 내리도록
        Player_white = 0;
        [self check_OK];
        [self change];
    }   
    
    else{
        Que.text = [NSString stringWithFormat:@"틀렸습니다"];
        btnEn = NO;
        [self btnEnable];
        //[NSTimer scheduledTimerWithTimeInterval:1.5 target:self selector:@selector(make_que) userInfo:nil repeats:NO];
        Player_blue =0;
        Player_white=0;
        flog =1;
        
    }
    
    
    
}


////////////////////////////////////////


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
    //AppDelegate의 데이터를 가져와서 쓴다
    appData = (AppDelegate*)[[UIApplication sharedApplication]delegate];
    
    //뽀로로의 초기이미지가 양손내림의 이미지이다.
    allDnImg = [UIImage imageNamed:@"LRDown.png"];
    ppororoView.image = allDnImg;
    
    
    //프로그래스바 초기화
    threadProgressView.progress = 0;
    
    //점수레이블 초기화면
    scoreLabel.text = [NSString stringWithFormat:@"%d",testScore];
    

    
    [super viewDidLoad];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


//2번재 뷰가 화면에 보여질때 네비게이션 바를 제거하고 프로그래스바의 움직임을
//시작한다. 또한 testScore값을 초기화 한다.
-(void)viewWillAppear:(BOOL)animated
{
    testScore = 0;
    
    //quizCnt값에 AppDelgate에 현재 입력된 문제숫자의 값을 넣어주어서
    //문제수 만큼 문제가 출력되도록 처리함.
    quizCnt = [appData.quizNumber intValue]+1;
    
    btnEn = NO;
    
    [self make_que];
    
    NSLog(@"%@",appData.quizNumber);
    
    [super viewWillAppear:animated];
}

-(void)viewWillDisappear:(BOOL)animated
{
    //화면이 넘어가면 숨겨두었던 네비게이션 바를 다시 나타내서 보여줌.
    [self.navigationController setNavigationBarHidden:NO animated:animated];
    
    //화면이 넘어가면 값 넘겨줌
    appData.gameScore = [NSNumber numberWithInt:testScore];
    
    [super viewWillDisappear:animated];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

@end
