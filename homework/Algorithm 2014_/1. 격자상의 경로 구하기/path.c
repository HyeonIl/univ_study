#include<stdio.h>
#define MAX 100

//��������
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
		//�迭 �� -1�� �ʱ�ȭ
		initArray();
		//��� ��ȣ �ۼ�
		makePath();

		//cirPos ������ 0�̶�� �ǹ̴� O�� ǥ�õ� ĭ�� �������� �ʴ� �ٴ� ���̴�.
		if(cirPos == 0){
			result = findPath(row,column);
			//cirPos ������ 0�� �ƴ϶�� �ٸ������ �����
		}else{
			//cirPos������ ���� ��ǥ���� ã�´�.
			searchCirPos();
			//��ǥ���� �̿��Ͽ� Oǥ�� ���� ��� ���� ���� ��ΰ��� ����
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

	//�ʱⰪ ����
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