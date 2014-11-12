#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 2000000
#define ROOT 1

FILE *input, *output;
int HEAP[MAX];
int heapCnt;
//===============================================
void insertKey(int keyNumber);				//�� ����
void swap(int *first, int *second);			//�ڸ� ����
void reportHeap();							//�� �����ֱ�
void deleteHeapRoot();						//�� ����
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
	//Heap�� ���� ���������
	if (HEAP[ROOT] == 0){
		HEAP[heapCnt] = keyNumber;
	} else {
		
		//���� heap�� ������ �ε����� key�� �����Ѵ�.
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
	//���������� ��Ʈ�� �ٲ�
	swap(&HEAP[ROOT], &HEAP[heapCnt]);
	//���������� 0���� �ʱ�ȭ
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
