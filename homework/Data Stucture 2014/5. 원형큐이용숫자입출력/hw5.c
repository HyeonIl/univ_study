#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Q_Size 5
#define TRUE 1

typedef struct cQ{
	int queue[5];
	int front;
	int rear;
}circleQ;

int isEmpty(circleQ *cQ);
int isFull(circleQ *cQ);
void enQueue(circleQ *cQ,int item);
int deQueue(circleQ *cQ);

int main(void)
{
	FILE *inp = fopen("hw5.inp","r");
	FILE *out = fopen("hw5.out","w");

	char command[10];
	int inpData;
	int i,first,last;

	//큐 생성 및 초기화
	circleQ cQ;
	cQ.front=0;
	cQ.rear=0;
	
	while(strcmp(command,"*"))
	{
		fscanf(inp,"%s",command);

		if(!strcmp(command,"en")){
			//enqueue 처리
			fscanf(inp,"%d",&inpData);
			//큐가 풀이면 에러 출력
			if(isFull(&cQ) == TRUE){
				fprintf(out,"error(full, %d)\n",inpData);
			}else{
				enQueue(&cQ,inpData);
			}
		}else if(!strcmp(command,"de")){
			//dequeue 처리
			//큐가 비어있으면 에러 출력
			if(isEmpty(&cQ)==TRUE){
				fprintf(out,"error(empty)\n");
			}else{
				fprintf(out,"%d\n",deQueue(&cQ));
			}
		}else if(!strcmp(command,"print_all")){
			//print all;
			if(isEmpty(&cQ)==TRUE){
				fprintf(out,"error(empty)\n");
			}else{
				//first에 front 다음값을 넣어주고, last에는 rear의 다음인덱스를 가르키게 한다.
				//rear가 가장 최근에 넣은 인덱스 이므로
				first = (cQ.front+1) % Q_Size;
				last = (cQ.rear+1) % Q_Size;
				for(i=first ; i!=last ; i=(i+1)%Q_Size)
				{
					if((i+1)% Q_Size == last){
						fprintf(out,"%d",cQ.queue[i]);
					}else{
						fprintf(out,"%d ",cQ.queue[i]);
					}
				}
				fprintf(out,"\n");
			}
		}
	}
	fprintf(out,"*");

	fclose(inp);
	fclose(out);

	return 0;
}
int isEmpty(circleQ *cQ)
{
	//front와 rear 값이 같다면 큐에 아무 값도 없다는 의미이다
	if(cQ->front == cQ->rear)
		return 1;
	else
		return 0;
}
int isFull(circleQ *cQ)
{
	//front의 인덱스가 가르키는 위치는 항상 비워두어야 한다.
	//따라서  rear+1 mod Q_size 값과 front 값이 같다는 것은 full이라는 의미이다
	if(((cQ->rear+1) % Q_Size) == cQ->front)
		return 1;
	else
		return 0;
}
void enQueue(circleQ *cQ,int item){
	cQ->rear = (cQ->rear + 1)% Q_Size;
	cQ->queue[cQ->rear] = item;
}
int deQueue(circleQ *cQ)
{
	cQ->front = (cQ->front + 1)% Q_Size;
	return cQ->queue[cQ->front];
}