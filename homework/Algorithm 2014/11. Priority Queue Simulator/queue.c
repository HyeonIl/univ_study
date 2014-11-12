#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 2000000
#define ROOT 1

FILE *input, *output;
int HEAP[MAX];
int heapCnt;
//===============================================
void insertKey(int keyNumber);				//힙 삽입
void swap(int *first, int *second);			//자리 교쳇
void reportHeap();							//힙 보여주기
void deleteHeapRoot();						//힙 삭제
//===============================================
int main()
{
	char buf[100];
	int keyNum;
	heapCnt = 1;

	input = fopen("queue.inp", "r");
	output = fopen("queue.out", "w");

	fscanf(input, "%s", buf);

	while (strcmp(buf,"q"))
	{
		if (!strcmp(buf, "d")){
			deleteHeapRoot();
		} else if (!strcmp(buf, "r")){
			reportHeap();
		} else {
			keyNum = atoi(buf);
			insertKey(keyNum);
		}
		fscanf(input, "%s", buf);
	}
	

	fclose(input);
	fclose(output);
	return 0;
}
void swap(int *first, int *second){
	int temp;

	temp = *first;
	*first = *second;
	*second = temp;
}
void insertKey(int keyNumber){
	int hpIdx;
	//Heap이 현재 비어있을때
	if (HEAP[ROOT] == 0){
		HEAP[heapCnt] = keyNumber;
	} else {
		
		//현재 heap의 마지막 인덱스에 key를 삽입한다.
		HEAP[++heapCnt] = keyNumber;
		hpIdx = heapCnt;
		while (HEAP[hpIdx / 2] < HEAP[hpIdx]){
			swap(&HEAP[hpIdx / 2], &HEAP[hpIdx]);
			hpIdx = hpIdx / 2;
			if (hpIdx == ROOT){
				break;
			}
		}
	}
}
void reportHeap(){
	int i;

	for (i = ROOT; i <= heapCnt; i *= 2){
		//printf("%d ", HEAP[i]);
		if (i == 1){
			fprintf(output, "%d", HEAP[i]);
		} else {
			fprintf(output, " %d", HEAP[i]);
		}
	}
	//printf("\n");
	fprintf(output,"\n");
}
void deleteHeapRoot(){
	int hpIdx = ROOT;
	int max;
	//마지막꺼랑 루트랑 바꿈
	swap(&HEAP[ROOT], &HEAP[heapCnt]);
	//마지막꺼는 0으로 초기화
	HEAP[heapCnt] = 0;
	heapCnt--;

	if (HEAP[hpIdx * 2] > HEAP[hpIdx * 2 + 1]){
		max = HEAP[hpIdx * 2];
	} else {
		max = HEAP[(hpIdx * 2) + 1];
	}

	while (max > HEAP[hpIdx]){
		if (HEAP[hpIdx * 2] > HEAP[hpIdx * 2 + 1]){
			swap(&HEAP[hpIdx], &HEAP[hpIdx * 2]);
			hpIdx *= 2;
		} else {
			swap(&HEAP[hpIdx], &HEAP[(hpIdx * 2) + 1]);
			hpIdx = (hpIdx * 2) + 1;
		}

		if (HEAP[hpIdx * 2] > HEAP[hpIdx * 2 + 1]){
			max = HEAP[hpIdx * 2];
		} else {
			max = HEAP[(hpIdx * 2) + 1];
		}
	}
}
