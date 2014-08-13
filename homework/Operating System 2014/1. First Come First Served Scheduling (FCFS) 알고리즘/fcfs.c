#include <stdio.h>
#include <stdlib.h>
#define MAX 50

typedef struct _process
{
	int pNum;
	int arriveTime;
	int burstTime;
	int waitTime;
}Process;
void ProcessSort(Process array[], int num);
int main()
{
	int num;
	int i;
	int totalTime = 0;
	int totalWaitTime = 0;
	FILE *input,*output;
	Process processors[MAX];

	input = fopen("fcfs.inp","r");
	output = fopen("fcfs.out","w");

	fscanf(input,"%d",&num);

	if(num>=50)
		printf("잘못된 값 입력 data error");

	for(i=0;i<num;i++)
	{
		fscanf(input,"%d %d %d",&(processors[i].pNum),&(processors[i].arriveTime),&(processors[i].burstTime));
	}

	//프로세스 정렬
	ProcessSort(processors,num);

	//FCFS Waiting Time 알고리즘
	/*********************************************************************************************************/
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

	/*********************************************************************************************************/


	//테스팅
	for(i=0;i<num;i++){
		printf("%d %d %d %d\n",processors[i].pNum,processors[i].arriveTime,processors[i].burstTime,processors[i].waitTime);
	}

	for(i=0;i<num;i++)
		totalWaitTime += processors[i].waitTime;

	//printf("합 : %d\n",totalWaitTime);

	fprintf(output,"%d",totalWaitTime);

	fclose(input);
	fclose(output);

	return 0;
}
//FCFS 정렬 알고리즘
void ProcessSort(Process array[], int num)
{
	int i,j;
	Process temp;
	//버블정렬을 이용하여 도착시간 순서대로 정렬
	for(i=0;i<num-1;i++){
		for(j=0;j<(num-i)-1;j++){
			if(array[j].arriveTime > array[j+1].arriveTime){
				temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
				//도착시간이 같으면 프로세스 번호가 작은것 앞으로
			}else if(array[j].arriveTime == array[j+1].arriveTime){
				if(array[j].pNum > array[j+1].pNum){
					temp = array[j];
					array[j] = array[j+1];
					array[j+1] = temp;
				}
			}
		}
	}
}//end ProcessSort
