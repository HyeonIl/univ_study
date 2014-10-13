#include<stdio.h>
#define MAX 50			//EDGE_MAX값 최종 500으로 바꺼야함
#define INFINITE 5000
#define TRUE 1

//===============전역 변수===============
FILE *input, *output;
int W[MAX][MAX];			//처음 입력받은 인접 행렬
int P[MAX][MAX];			//S 에서 V 까지의 경로가 적힌곳
int P2[MAX][MAX];			//V 에서 T 까지의 경로가 적힌곳
int SV[MAX][MAX];			//S 에서 V 까지의 거리
int VT[MAX][MAX];			//V 에서 T 까지의 거리
//---------------------------------------
void initArray();							//배열 초기화
void makePath(int path1[][MAX], int path2[][MAX]);	//P2의 값을 P에 대입하는 함수
void floyd(int pass,int Dd[][MAX],int Pp[][MAX]);	//pass변수의 값을 건너뛰어서 그 경로를 지나지 않게 한다.
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

	//배열에 무한대값 일단 떄려박음
	for (i = 0; i < MAX; i++){
		for (j = 0; j < MAX; j++){
			W[i][j] = INFINITE;
		}
	}
	fscanf(input, "%d %d", &vertex, &edge);

	//입력받아서 인접행렬 W생성
	for (i = 0; i < edge; i++){
		fscanf(input, "%d %d %d", &start, &end, &weight);
		W[start][end] = weight;
	}
	initArray();


	while (TRUE){
		fscanf(input, "%d %d %d", &S, &V, &T);
		if (S == -1 && V == -1 && T == -1) { break; }
			floyd(T,SV,P);
			distance1 = SV[S][V];	//S 에서 V까지의 거리
			floyd(S,VT,P2);
			distance2 = VT[V][T];	//V 에서 T까지의 거리
		if (distance1 + distance2 > INFINITE){	//만약 그것이 무한대값 보다 크다면 이것은 경로가 없는것이다.
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