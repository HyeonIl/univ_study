#include<stdio.h>
#define MAX 100		//MAX값 바꾸짜

//=================전역 변수================
FILE *input, *output;
int matrix[MAX][MAX];
int SUM[MAX][MAX];
//==========================================
void inputData(int length);		//데이터 입력받아서 행렬에 저장
void initArray();				//배열 초기화
int findMAX2D(int length);		//구하는 로직
int max(int first, int second); //둘중 큰값을 리턴하는 함수
//==========================================
int main()
{
	int testCase;
	int number;
	int result;

	input = fopen("sum.inp", "r");
	output = fopen("sum.out", "w");

	fscanf(input, "%d", &testCase);

	while (testCase--){
		fscanf(input, "%d", &number);

		/*배열 초기화*/
		initArray();

		/*데이터 입력*/
		inputData(number);

		/*부분행렬 찾는 로직*/
		result = findMAX2D(number);

		/*출력*/
		fprintf(output,"%d\n", result);
	}

	fclose(input);
	fclose(output);
}
void inputData(int length){
	int i, j;
	int data;
	int tempSUM = 0;

	for (i = 0; i < length; i++){
		for (j = 0; j < length; j++){
			fscanf(input, "%d", &data);
			matrix[i][j] = SUM[i][j] = data;
		}
	}

}
void initArray(){
	int i, j;

	for (i = 0; i < MAX; i++){
		for (j = 0; j < MAX; j++){
			matrix[i][j] = SUM[i][j] = -9999;
		}
	}
}
int findMAX2D(int length){

	int i, j, k, l;
	int sum = 0;

	SUM[0][0] = matrix[0][0];

	//일단 1번행과 1번열을 더합니다
	for (i = 1; i < length; i++){
		SUM[0][i] = SUM[0][i - 1] + SUM[0][i];
		SUM[i][0] = SUM[i - 1][0] + SUM[i][0];
	}
	//SUM행렬의 좌표 값은 0,0에서 그 좌표까지의 행렬의 합이다.
	//이 SUM행렬을 가지고 DP로 문제를 해결한다
	for (i = 1; i < length; i++){
		for (j = 1; j < length; j++){
			SUM[i][j] = SUM[i][j] + SUM[i - 1][j] + SUM[i][j - 1] - SUM[i - 1][j - 1];
		}
	}

	for (l = 0; l < length; l++){
		for (k = 0; k < length; k++){
			for (i = l; i < length; i++){
				for (j = k; j < length; j++){
					if (l > 0 && k > 0){
						//l 과 k 가 1 이상일때는 중복으로 빼주는 영역이 있으므로 그부분을 다시 더한다
						sum = max(sum, (SUM[i][j] - SUM[i - l][j] - SUM[i][j - k] + SUM[i - l][j - k]));
						continue;
					} else if (l > 0){
						sum = max(sum, SUM[i][j] - SUM[i - l ][j]);
						continue;
					} else if (k > 0){
						sum = max(sum, SUM[i][j] - SUM[i][j-k]);
						continue;
					} else{
						sum = max(sum, SUM[i][j]);
					}
				}
			}
		}
	}
	return sum;
}
int max(int first, int second){
	if (first > second){
		return first;
	} else
		return second;
}