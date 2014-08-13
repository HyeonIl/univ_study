#include <stdio.h>
#include <stdlib.h>
#define MAX 50
#define TRUE 1
#define FALSE 0

typedef struct _process
{
	int pNum;
	int arriveTime;
	int burstTime;
	int waitTime;
}Process;
int compare(const void *val1,const void *val2);
int rqCompare(const void *val1,const void *val2);
int main()
{
	int num;
	int i,j,fix,rqi2=0;
	int counter = 0;
	int rqIndex = 0;
	int finishTime = 0;
	int totalTime = 0;
	int totalWaitTime = 0;
	FILE *input,*output;
	Process processors[MAX] = {0,};
	Process readyQueue[MAX];
	Process temp;

	input = fopen("sjf.inp","r");
	output = fopen("sjf.out","w");

	fscanf(input,"%d",&num);

	if(num>=50)
		printf("잘못된 값 입력 data error");

	for(i=0;i<num;i++)
	{
		fscanf(input,"%d %d %d",&(processors[i].pNum),&(processors[i].arriveTime),&(processors[i].burstTime));
	}

	//SJF정렬 알고리즘
	//***************************************************************************************************//
	//1. 도착시간 -> cpu사용시간 -> 프로세스 번호순으로 1차정렬
	qsort(processors,num,sizeof(Process),compare);
	//fix값은 프로세스 우선순위가 결정된 것을 의미한다 초기값은 0이고 1번째 프로세스가 실행되면 fix값이 증가함
	fix=0;
	//첫번째로 실행되는 프로세스는 사용시간 + 도착시간이 종료시간이다
	finishTime += (processors[0].arriveTime + processors[0].burstTime);

	while(TRUE){
		//프로세스의 종료시간 보다 그 다음 프로세스의 도착시간이 작고 종료시간과 그 다음다음 프로세스의 도착시간이 같지 않으면
		if(finishTime > processors[fix+1].arriveTime && finishTime !=processors[fix+2].arriveTime){
			for(i=fix;i<num-1 && finishTime > processors[i+1].arriveTime;i++){
				//레디큐에 넣음
				readyQueue[rqIndex++] = processors[i+1];
			}
			//레디큐를 cpu사용시간 순으로 정렬
			qsort(readyQueue,rqIndex,sizeof(Process),rqCompare);
			//첫번째 프로세스가 실행됬으므로 fix값 1 증가
			fix++;
			//레디큐에 정렬된 값을 프로세스들의 배열에 다시 대입
			for(i=0;i<rqIndex;i++)
				processors[i+fix] = readyQueue[rqi2++];
			rqIndex = 0;
			rqi2=0;
			//종료시간은 그다음프로세스가 실행된 시간을 더하는 값이다.
			finishTime+=processors[fix].burstTime;
			//종료시간과 다음다음 프로세스의 실행시간이 같을 경우 순서를 바꾼다
		}else if(finishTime == processors[fix+2].arriveTime){
			if(processors[fix+1].burstTime > processors[fix+2].burstTime){
				temp = processors[fix+1];
				processors[fix+1] = processors[fix+2];
				processors[fix+2] = temp;
			}
		}else{
			//다음프로세스의 도착시간이 매우 늦어서 레디큐가 필요하지 않을때 종료시간은 도착시간 + 사용시간
			finishTime = processors[fix+1].burstTime + processors[fix+1].arriveTime;
			//역시 마찬가지로 프로세스가 실행됫으므로 fix값 1증가
			fix++;
		}
		//counter 변수를 선언하여서 while문 탈출
		counter ++;
		if(counter == num)
			break;
	}


	///*
	//SJF Waiting Time 알고리즘
	//***************************************************************************************************//
	for(i=0;i<num;i++){
		if(i==0){
			totalTime += processors[i].arriveTime + processors[i].burstTime;
			processors[0].waitTime = 0;
		}else{
			if(processors[i].arriveTime <= totalTime){ //총걸린시간보다 프로세서 도착시간이 작으면
				processors[i].waitTime = totalTime - processors[i].arriveTime;
				totalTime += processors[i].burstTime;
			}else{
				processors[i].waitTime = 0;
				totalTime = (processors[i].burstTime + processors[i].arriveTime);
			}

			//totalTime += processors[i].burstTime;
			//processors[i].waitTime = totalTime - processors[i].arriveTime - processors[i].burstTime;
		}
	}
	//***************************************************************************************************//
	//*/

	//테스팅
	printf("  pNum   arrTime   burstTime   waitTime\n");
	for(i=0;i<num;i++){
		printf("%7d %9d %9d %9d\n",processors[i].pNum,processors[i].arriveTime,processors[i].burstTime,processors[i].waitTime);
	}

	for(i=0;i<num;i++)
		totalWaitTime += processors[i].waitTime;

	printf("합 : %d\n",totalWaitTime);

	fprintf(output,"%d",totalWaitTime);

	fclose(input);
	fclose(output);

	return 0;
}
//SJF 정렬 알고리즘
int compare(const void *val1,const void *val2)
{
	int arrTime1 = ((Process*)val1)->arriveTime;
	int arrTime2 = ((Process*)val2)->arriveTime;

	int processNum1 = ((Process*)val1)->pNum;
	int processNum2 = ((Process*)val2)->pNum;

	int burstTime1 = ((Process*)val1)->burstTime;
	int burstTime2 = ((Process*)val2)->burstTime;

	//도착시간이 작은순서대로 오름차순 정렬 compare함수는 음수값을 반환해야 오름차순 정렬이다.
	if(arrTime1 < arrTime2)
		return -1;
	//도착시간이 같으면 burstTime이 작은 순으로 정렬
	else if(arrTime1 == arrTime2){
		if(burstTime1 < burstTime2)
			return -1;
		//burstTime마저 같으면 프로세스 번호로 정렬
		else if(burstTime1 == burstTime2){
			if (processNum1 < processNum2){
				return -1;
			}
		}else{
			return 1;
		}
	}
}
int rqCompare(const void *val1,const void *val2)
{
	int processNum1 = ((Process*)val1)->pNum;
	int processNum2 = ((Process*)val2)->pNum;

	int burstTime1 = ((Process*)val1)->burstTime;
	int burstTime2 = ((Process*)val2)->burstTime;

	if(burstTime1 < burstTime2) 
		return -1;
	else if(burstTime1 == burstTime2){
		if (processNum1 < processNum2) 
			return -1;
	}
	else
		return 1;
}
