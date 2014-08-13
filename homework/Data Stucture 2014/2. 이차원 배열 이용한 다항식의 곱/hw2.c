#include <stdio.h>
#include <stdlib.h>
#define MAX 100

enum polyNumber
{
	deg,coef
};
typedef struct _poly
{
	int arr[MAX][2];
	int length;
}Poly;
void BubbleSort(Poly tempPoly[],int number);
int main()
{
	FILE *input;
	FILE *output;

	char endcheck,trash=0;
	int i,j,k,cnt=0;
	int maxDegree,polyNum;
	int tempIndex = 0;

	Poly firPoly = {0,};
	Poly secPoly = {0,};
	Poly tempPoly = {0,};
	int swapData[2];

	//************************예외처리****************************//
	if(( input = fopen("hw2.inp", "r")) == NULL ){
		fprintf(stderr, "can't open %s\n", "hw2.inp" );
	}
	if(( output = fopen("hw2.out", "w")) == NULL ){
		fprintf(stderr, "can't open %s\n", "hw2.out" );
	}
	//***********************************************************// 


	//*******************************************************************************//
	for(k=0;k<2;k++){
		if(cnt==0){
			for(i=0;i<MAX;i++){
				fscanf(input,"%c",&endcheck);
				if(endcheck=='*') break;
				fscanf(input,"%d,%d]\n",&firPoly.arr[i][deg],&firPoly.arr[i][coef]);
				firPoly.length++;
			}
			cnt++;
			fputc(trash,input);
		}else{
			for(j=0;j<MAX;j++){
				fscanf(input,"%c",&endcheck);
				if(endcheck=='*') break;
				fscanf(input,"%d,%d]\n",&secPoly.arr[j][0],&secPoly.arr[j][1]);
				secPoly.length++;
			}
		}
	}

	//입력값 정렬함
	BubbleSort(&firPoly,firPoly.length);
	BubbleSort(&secPoly,secPoly.length);

	for(i=0;i<firPoly.length;i++){
		for(j=0;j<secPoly.length;j++)
		{
			//지수끼리는 더하고 계수끼리는 곱해서 임시 배열에 저장
			tempPoly.arr[tempIndex][deg] = firPoly.arr[i][deg] + secPoly.arr[j][deg];
			tempPoly.arr[tempIndex++][coef] = firPoly.arr[i][coef] * secPoly.arr[j][coef];
		}
	}

	//일단 한번 계산이 진행된 상태로의 항의 갯수를 구한다
	polyNum = firPoly.length * secPoly.length;

	for(i=0;i<polyNum;i++){
		for(j=i+1;j<polyNum;j++){
			//차수가 같으면 더해줌
			if(tempPoly.arr[i][deg] == tempPoly.arr[j][deg])
			{
				tempPoly.arr[i][coef] += tempPoly.arr[j][coef];
				tempPoly.arr[j][deg] = 0;
				tempPoly.arr[j][coef] = 0;
			}
		}
	}

	//더해진 값 다시한번 정렬
	BubbleSort(&tempPoly,polyNum);


	//test
	for(k=0;k<MAX;k++){
		//계수가 0이면 출력 생깜~
		if(tempPoly.arr[k][coef] == 0){
			continue;
		}
		printf("%4d %4d\n",tempPoly.arr[k][deg],tempPoly.arr[k][coef]);
		fprintf(output,"[%d,%d]\n",tempPoly.arr[k][deg],tempPoly.arr[k][coef]);
	}
	fprintf(output,"*");

	fclose(input);
	fclose(output);
	return 0;
}
void BubbleSort(Poly tempPoly[],int number){
	int swapData[2];
	int i,j;
	for(i=0;i<number;i++){
		for(j=0;j<number-i-1;j++)
		{
			if((*tempPoly).arr[j][deg] < (*tempPoly).arr[j+1][deg]){
				swapData[deg] = (*tempPoly).arr[j][deg];
				swapData[coef] = (*tempPoly).arr[j][coef];
				(*tempPoly).arr[j][deg] = (*tempPoly).arr[j+1][deg];
				(*tempPoly).arr[j][coef] = (*tempPoly).arr[j+1][coef];
				(*tempPoly).arr[j+1][deg] = swapData[deg];
				(*tempPoly).arr[j+1][coef] = swapData[coef];
			}
		}
	}
}
