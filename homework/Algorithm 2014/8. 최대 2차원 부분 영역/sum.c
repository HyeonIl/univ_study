#include<stdio.h>
#define MAX 100		//MAX�� �ٲ�¥

//=================���� ����================
FILE *input, *output;
int matrix[MAX][MAX];
int SUM[MAX][MAX];
//==========================================
void inputData(int length);		//������ �Է¹޾Ƽ� ��Ŀ� ����
void initArray();				//�迭 �ʱ�ȭ
int findMAX2D(int length);		//���ϴ� ����
int max(int first, int second); //���� ū���� �����ϴ� �Լ�
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

		/*�迭 �ʱ�ȭ*/
		initArray();

		/*������ �Է�*/
		inputData(number);

		/*�κ���� ã�� ����*/
		result = findMAX2D(number);

		/*���*/
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

	//�ϴ� 1����� 1������ ���մϴ�
	for (i = 1; i < length; i++){
		SUM[0][i] = SUM[0][i - 1] + SUM[0][i];
		SUM[i][0] = SUM[i - 1][0] + SUM[i][0];
	}
	//SUM����� ��ǥ ���� 0,0���� �� ��ǥ������ ����� ���̴�.
	//�� SUM����� ������ DP�� ������ �ذ��Ѵ�
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
						//l �� k �� 1 �̻��϶��� �ߺ����� ���ִ� ������ �����Ƿ� �׺κ��� �ٽ� ���Ѵ�
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