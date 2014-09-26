#include<stdio.h>
#define MAX 100

//전역변수
FILE *input,*output;
int pathArray[MAX][MAX];
int row,column;
int cirPos;
struct position{
	int x;
	int y;
}pos;
//----------------------------------------------------
void initArray();
void makePath();
void searchCirPos();
int findPath(int row_s,int column_s);
//----------------------------------------------------
int main()
{
	int testCase;
	int first,second;
	int result;

	input = fopen("path.inp","r");
	output = fopen("path.out","w");
	fscanf(input,"%d",&testCase);

	while(testCase--){
		//배열 값 -1로 초기화
		initArray();
		//경로 번호 작성
		makePath();

		//cirPos 변수가 0이라는 의미는 O로 표시된 칸이 존재하지 않는 다는 뜻이다.
		if(cirPos == 0){
			result = findPath(row,column);
			//cirPos 변수가 0이 아니라면 다른방법을 사용함
		}else{
			//cirPos변수가 적힌 좌표값을 찾는다.
			searchCirPos();
			//좌표값을 이용하여 O표시 앞의 경로 값과 뒤의 경로값을 곱함
			first = findPath(pos.x+1,pos.y+1);
			second = findPath(row-pos.x,column-pos.y);
			result = first * second;
		}
		fprintf(output,"%d\n",result);
	}

	fclose(input);
	fclose(output);
	return 0;
}
void initArray()
{
	int i,j;

	for(i=0; i<MAX; i++){
		for(j=0; j<MAX; j++){
			pathArray[i][j] = -1;
		}
	}
}
void makePath(){
	int i,j;
	int number = 1;

	fscanf(input,"%d %d %d",&row,&column,&cirPos);
	for(i=0; i<row; i++){
		for(j=0; j<column; j++){
			pathArray[i][j] = number++;
		}
	}
}
void searchCirPos()
{
	int i,j;
	for(i=0; i<row; i++){
		for(j=0; j<column; j++){
			if(pathArray[i][j] == cirPos){
				pos.x = i;
				pos.y = j;
				//return pos;
			}
		}
	}
}
int findPath(int row_s,int column_s)
{
	int i,j;
	int dfsArray[MAX][MAX];

	//초기값 설정
	for(i=0; i<column_s; i++){
		dfsArray[0][i] = 1;
	}
	for(j=0; j<row_s; j++){
		dfsArray[j][0] = 1;
	}

	for(i=1; i<=row_s; i++){
		for(j=1; j<=column_s; j++){
			dfsArray[i][j] = dfsArray[i-1][j] + dfsArray[i][j-1];
		}
	}

	return dfsArray[row_s-1][column_s-1];
}