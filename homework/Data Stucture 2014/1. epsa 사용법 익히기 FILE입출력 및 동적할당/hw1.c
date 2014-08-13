#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 20

enum subNum{
	KOR,ENG,MATH
};
typedef struct _score{
	int sub[3];
}Score;

//함수 정의
double RoundNumber(double number);			//소수점 버림 함수
double StDevia(double average[],Score array[],int arrSize,int option); //표준편차 구하는 함수

int main()
{
	//변수 선언
	char star = '*';
	int num,i;
	int *sum;
	double aver[3],devia[3];

	FILE *input_fp, *output_fp;
	Score students[MAX];

	/******************************************************************/
	//예외처리 부분
	if(( input_fp = fopen("hw1.inp", "r")) == NULL )
	{
		fprintf(stderr, "can't open %s\n", "hw1.inp" );
	}
	if(( output_fp = fopen("hw1.out", "w")) == NULL )
	{
		fprintf(stderr, "can't open %s\n", "hw1.out" );
	}
	if( ( sum = (int *)malloc( sizeof(int)*3 )) == NULL )
	{
		fprintf(stderr, "memory allocation error %s\n", "sum" );
	}
	/******************************************************************/
	//sum 변수 초기화
	sum[KOR]=0;
	sum[ENG]=0;
	sum[MATH]=0;
	fscanf(input_fp,"%d",&num);

	for(i=0;i<num;i++){
		fscanf(input_fp,"%d %d %d",&(students[i].sub[KOR]),&(students[i].sub[ENG]),&(students[i].sub[MATH]));
		sum[KOR] += students[i].sub[KOR];
		sum[ENG] += students[i].sub[ENG];
		sum[MATH] += students[i].sub[MATH];
	}

	//평균
	aver[KOR] = RoundNumber((double)sum[KOR]/num);
	aver[ENG] = RoundNumber((double)sum[ENG]/num);
	aver[MATH] = RoundNumber((double)sum[MATH]/num);

	fprintf(output_fp,"%.1lf %.1lf %.1lf\n",aver[KOR],aver[ENG],aver[MATH]);
	//printf("%.1lf %.1lf %.1lf\n",aver[KOR],aver[ENG],aver[MATH]);

	//표준편차
	devia[KOR] = StDevia(aver,students,num,KOR);
	devia[ENG] = StDevia(aver,students,num,ENG);
	devia[MATH] = StDevia(aver,students,num,MATH);

	fprintf(output_fp,"%.1lf %.1lf %.1lf\n",devia[KOR],devia[ENG],devia[MATH]);
	//printf("%.1lf %.1lf %.1lf\n",devia[KOR],devia[ENG],devia[MATH]);

	//*삽입
	fputc(star,output_fp);
	//putchar(star);
	//puts("");

	fclose(input_fp);
	fclose(output_fp);
	free(sum);

	return 0;
}
double RoundNumber(double number)
{
	int var1 = number*10;
	return (double)var1/10;
}
double StDevia(double average[],Score array[],int arrSize,int option){

	double deviaValue=0;
	int i,temp;
	for(i=0;i<arrSize;i++)
	{
		deviaValue += (array[i].sub[option]-average[option])*(array[i].sub[option]-average[option]);
	}

	temp = sqrt((deviaValue/arrSize))*10;

	//return (double)temp/10;

	return RoundNumber(sqrt(deviaValue/arrSize));
}