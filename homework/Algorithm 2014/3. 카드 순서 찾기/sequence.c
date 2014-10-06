#include<stdio.h>
#include<stdlib.h>
#define MAX 1000

//��������
FILE *input,*output;
int S[MAX];
int C[MAX];
int sortArray[MAX];
//-----------------------------------------------
int compare(const void *a, const void *b);
int updateArray(int index);
//-----------------------------------------------
int main()
{
	int testCase;
	int i;
	int inputNumber;

	input = fopen("sequence.inp", "r");
	output = fopen("sequence.out", "w");

	fscanf(input, "%d", &testCase);

	//�Է�
	for (i = 0; i < testCase; i++){
		fscanf(input, "%d", &inputNumber);
		S[i] = inputNumber;
		sortArray[i] = inputNumber;
	}
	for (i = 0; i < testCase; i++){
		fscanf(input, "%d", &C[i]);
	}

	//����
	qsort(sortArray,testCase,sizeof(sortArray[0]),compare);


	for(i=testCase-1; i>-1; i--){
		S[i] = sortArray[C[i]];
		//������ ������ ī��� ���ܽ��Ѽ� �迭�� ������.
		updateArray(C[i]);
	}

	for(i=0; i<testCase; i++){
		fprintf(output,"%d\n",S[i]);
	}


	fclose(input);
	fclose(output);
	return 0;
}
int updateArray(int index)
{
	int i;
	for(i=index; i<MAX-1; i++){
		sortArray[i] = sortArray[i+1];
	}
}
int compare(const void *a, const void *b)
{
	int first, second;
	first = *((int*)a);
	second = *((int*)b);

	//������������ ����
	if (first > second)
		return 1;
	else if (first < second)
		return -1;
	else
		return 0;
}