#include<stdio.h>
#define MAX 50			//EDGE_MAX�� ���� 500���� �ٲ�����
#define INFINITE 5000
#define TRUE 1

//===============���� ����===============
FILE *input, *output;
int W[MAX][MAX];			//ó�� �Է¹��� ���� ���
int P[MAX][MAX];			//S ���� V ������ ��ΰ� ������
int P2[MAX][MAX];			//V ���� T ������ ��ΰ� ������
int SV[MAX][MAX];			//S ���� V ������ �Ÿ�
int VT[MAX][MAX];			//V ���� T ������ �Ÿ�
//---------------------------------------
void initArray();							//�迭 �ʱ�ȭ
void makePath(int path1[][MAX], int path2[][MAX]);	//P2�� ���� P�� �����ϴ� �Լ�
void floyd(int pass,int Dd[][MAX],int Pp[][MAX]);	//pass������ ���� �ǳʶپ �� ��θ� ������ �ʰ� �Ѵ�.
void path(int q, int r);
//---------------------------------------
int main()
{
	int vertex = 0, edge = 0;
	int start, end, weight;
	int S, V, T;
	int i,j;
	int distance1,distance2;

	input = fopen("path.inp", "r");
	output = fopen("path.out", "w");

	//�迭�� ���Ѵ밪 �ϴ� ��������
	for (i = 0; i < MAX; i++){
		for (j = 0; j < MAX; j++){
			W[i][j] = INFINITE;
		}
	}
	fscanf(input, "%d %d", &vertex, &edge);

	//�Է¹޾Ƽ� ������� W����
	for (i = 0; i < edge; i++){
		fscanf(input, "%d %d %d", &start, &end, &weight);
		W[start][end] = weight;
	}
	initArray();


	while (TRUE){
		fscanf(input, "%d %d %d", &S, &V, &T);
		if (S == -1 && V == -1 && T == -1) { break; }
			floyd(T,SV,P);
			distance1 = SV[S][V];	//S ���� V������ �Ÿ�
			floyd(S,VT,P2);
			distance2 = VT[V][T];	//V ���� T������ �Ÿ�
		if (distance1 + distance2 > INFINITE){	//���� �װ��� ���Ѵ밪 ���� ũ�ٸ� �̰��� ��ΰ� ���°��̴�.
			fprintf(output, "%d %d %d (-1)\n", S, V, T);
			initArray();
			continue;
		}
			fprintf(output, "%d", S);
			path(S, V);
			fprintf(output, " %d", V);
			makePath(P, P2);
			path(V, T);
			fprintf(output," %d (%d)\n", T,distance1+distance2);
			initArray();
	}

	fclose(input);
	fclose(output);
	return 0;
}
void initArray(){
	int i, j;
	for (i = 0; i < MAX; i++){
		for (j = 0; j < MAX; j++){
			SV[i][j] = W[i][j];
			VT[i][j] = W[i][j];
		}
	}
	for (i = 0; i < MAX; i++){
		for (j = 0; j < MAX; j++){
			P[i][j] = -1;
			P2[i][j] = -1;
		}
	}
}
void floyd(int pass, int Dd[][MAX], int Pp[][MAX]){
	int i, j, k;

	for (k = 0; k < MAX; k++){
		if (k == pass) { continue; }
		for (i = 0; i < MAX; i++){
			for (j = 0; j < MAX; j++){
				if (Dd[k][j] + Dd[i][k] < Dd[i][j]){
					Pp[i][j] = k;
					Dd[i][j] = Dd[i][k] + Dd[k][j];
				}
			}
		}
	}//end for
}
void makePath(int path1[][MAX], int path2[][MAX]){
	int i, j;
	for (i = 0; i < MAX; i++){
		for (j = 0; j < MAX; j++){
			path1[i][j] = path2[i][j];
		}
	}
}
void path(int q,int r){
	if (P[q][r] != -1){
		path(q, P[q][r]);
		fprintf(output, " %d", P[q][r]);
		path(P[q][r], r);
	}
}