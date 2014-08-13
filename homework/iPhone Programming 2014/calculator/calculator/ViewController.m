//
//  ViewController.m
//  calculator
//
//  Created by 동아 on 14. 5. 2..
//  Copyright (c) 2014년 __MyCompanyName__. All rights reserved.
//

#import "ViewController.h"
const NSString *OPERATOR = @"+/-x=";
@implementation ViewController
@synthesize currentLabel,totalLabel,statSwitch,fontChanger;

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    //초기화는 모두 ViewDidLoad에서 수행함
    
    fontChanger.minimumValue = 10;
    fontChanger.maximumValue = 30;
    
    
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

-(IBAction)numberTouch:(id)sender
{
    
    //statSwitch가 현재 On일떄만 수정이 가능함!!
    if(statSwitch.on ==YES){
        //operCheck를 체크 하여서 TRUE라는 것은 계산 결과값이 현재 레이블에
        //출력되고 있다는 것이므로 공백으로 초기화 시킨다.
        if(operCheck == TRUE){
            currentLabel.text = @"";
        }
        //sender를 통해서 하나의 메소드로 여러 이벤트의 입력을 받을 수 있게 함
        //curText에 현재 눌러진 sender의 타이틀을 저장한다.
        NSString *curText = [sender titleForState:UIControlStateNormal];
        //currrentLabel의 텍스트에 curText값을 붙여서 totalInput에 저장한다.
        NSString *totalInput = [currentLabel.text stringByAppendingFormat:@"%@",curText];
        NSString *fomular = [totalLabel.text stringByAppendingFormat:@"%@",curText];
    
        currentLabel.text = totalInput;
        totalLabel.text = fomular;
        curData = [totalInput intValue];
        
        operCheck = FALSE;
    }else{
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"수정가능여부" message:@"수정불가능합니다!!" delegate:self cancelButtonTitle:nil otherButtonTitles:@"확인", nil];
        [alert show];
        //NSLog(@"수정불가!!");
    }
}

-(IBAction)operTouch:(id)sender
{
    //statSwitch가 현재 On일떄만 수정이 가능함!!
    if(statSwitch.on == YES)
    {
        //현재 눌려진 버튼의 노말상태의 타이틀(텍스트)를 가져온다.
        NSString *curOper = [sender titleForState:UIControlStateNormal];
        
        //lastChar변수로 마지막 입력캐릭터를 저장함        length-1 값으로 마지막 인덱스에 해당하는 값 저장함 그게 lastChar에 저장됨
        lastChar = [totalLabel.text substringFromIndex:[totalLabel.text length]-1];
        
        //lastChar와 OPEATOR문자열 상수를 비교하여 연산자가 있으면 그값은 1이상 이므로 참이라는 것은 마지막문자가 연산자라는 의미이다 따라서 처리안함
        if([OPERATOR rangeOfString:lastChar].length){
        
        }else{
            //totalLabel 에 현재 진행된 식들을 보여준다.
            NSString *totalFomula = [totalLabel.text stringByAppendingFormat:@"%@",curOper];
            totalLabel.text = totalFomula;
            if(totalResult != 0){
                if([preOper isEqualToString:@"+"] == TRUE){
                    totalResult = totalResult + curData;
                }else if([preOper isEqualToString:@"-"] == TRUE){
                    totalResult = totalResult - curData;
                }else if([preOper isEqualToString:@"x"] == TRUE){
                    totalResult = totalResult * curData;
                }else if([preOper isEqualToString:@"/"] == TRUE){
                    totalResult = totalResult / curData;
                }
            }else{
                //계산된 결과가 0이면 현재까지 입력된 숫자를 저장
                totalResult = curData;
            }
            
            curData = 0;
            //밑에꺼는 식의 결과 출력시킴
            currentLabel.text = [NSString stringWithFormat:@"%d",totalResult];
            
            //이전연산자는 현재연산자로 업뎃
            preOper = curOper;
            
            //"="이 입력으로 들어오면 연산의 결과 출력하고 나머지 0과 nil로 초기화
            if([curOper isEqualToString:@"="] == TRUE)
            {
                currentLabel.text = [NSString stringWithFormat:@"%d",totalResult];
                preOper = nil;
                totalResult = 0;
                curOper = nil;
                curData = 0;
            }
        }
        
        operCheck = TRUE;
        
    }else{
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"수정가능여부" message:@"수정불가능합니다!!" delegate:self cancelButtonTitle:nil otherButtonTitles:@"확인", nil];
        [alert show];
    }

}

-(IBAction)Deletedata
{
    //삭제연산을 수행하기 위해 NSMutableString클래스에 total값 저장
    NSMutableString *delTotalFomular = [[NSMutableString alloc]initWithFormat:totalLabel.text];
    //Range클래스를 이용하여 삭제연산을 수행하는데
    //totalLabe.text의 길이에 -1 한 값이 마지막 인덱스에 1개의 문자에 해당
    //하는 값을 삭제 시킨다.
    [delTotalFomular deleteCharactersInRange:NSMakeRange([totalLabel.text length]-1,1)];
    totalLabel.text = delTotalFomular;
    
    
    //currentLabel도 똑같이 처리한다.
    /*
    NSMutableString *delCurLabel = [[NSMutableString alloc]initWithFormat:currentLabel.text];
    [delCurLabel deleteCharactersInRange:NSMakeRange([currentLabel.text length]-1, 1)];
    currentLabel.text = delCurLabel;
     */
}


-(IBAction)ClearData
{
    currentLabel.text = @"";
    totalLabel.text = @"";
    totalResult = 0;
}

-(IBAction)changeFont
{
    if(statSwitch.on ==YES){
        currentLabel.font = [UIFont systemFontOfSize:fontChanger.value];
    }else{
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"수정가능여부" message:@"수정불가능합니다!!" delegate:self cancelButtonTitle:nil otherButtonTitles:@"확인", nil];
        [alert show];
    }
}


-(IBAction)statChange
{
    if(statSwitch.on == YES){
        currentLabel.enabled = YES;
    }else{
        currentLabel.enabled = NO;
    }
}

@end
