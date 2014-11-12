#include<stdio.h>
#include<string.h>
#define PATH_MAX 101
#define K_MAX 201
#define TRUE 1
#define FALSE 0
#define UP 8
#define LEFT 4

typedef struct _path{
	int right;
	int down;
	int x_chk;
	int count[K_MAX];					//경로의 갯수
	int cost[K_MAX];					//경로의 가중치
	int pass[K_MAX];					//지나온 경로 방향
}Path;
typedef struct _pos{
	int x, y;
}Pos;
//=================전역 변수================
FILE *input, *output;
Path PATH[PATH_MAX][PATH_MAX];
int M, N, K;
int number;
//==========================================
void inputData();
void findAnswer();
void moveK(int kArr[]);
void copyK(int start[], int dest[]);
void mergeK(int first[], int second[], int dest[]);
void initData();
void printAnswer();
void findPass(int number);		//경로 찾는 로직 함수
//==========================================
int main(void)
{
	int testCase;
	number = 1;

	input = fopen("path.inp", "r");
	output = fopen("path.out", "w");

	fscanf(input, "%d", &testCase);

	while (testCase--){
		fscanf(input, "%d %d %d", &M, &N, &K);
		inputData();
		
		findAnswer();
		printAnswer();
		initData();		
	}

	fclose(input);
	fclose(output);
	return 0;
}
void inputData(){
	int x, y;
	int i, j;

	//X가 마크된 좌표값을 입력받는다.

	for (i = 0; i < K; i++){
		fscanf(input, "%d %d", &x, &y);
		PATH[x][y].x_chk = TRUE;
	}

	//오른쪽 경로의 가중치 입력받음
	for (i = 0; i < M; i++){
		for (j = 0; j < N - 1; j++){
			fscanf(input, "%d", &PATH[i][j].right);
		}
	}

	//아래쪽 경로의 가중치 입력받음
	for (i = 0; i < M - 1; i++){
		for (j = 0; j < N; j++){
			fscanf(input, "%d", &PATH[i][j].down);
		}
	}
}
void findAnswer(){
	int i, j, k;
	int countI1, countJ1;
	int kCnt = 0;

	PATH[0][0].count[0] = 1;
	//만약 시작점인 (0,0)에 x 마크가 있을때
	if (PATH[0][0].x_chk == TRUE){
		moveK(PATH[0][0].count);
	} else {
	//아니라면 첫번째줄 채운다
		for (i = 1; i < M; i++){
			copyK(PATH[i - 1][0].count, PATH[i][0].count);
			copyK(PATH[i - 1][0].cost, PATH[i][0].cost);
			PATH[i][0].cost[kCnt] += PATH[i - 1][0].down;
			PATH[i][0].pass[kCnt] = UP;
			if (PATH[i][0].x_chk == TRUE){
				moveK(PATH[i][0].count);
				moveK(PATH[i][0].cost);
				moveK(PATH[i][0].pass);
				kCnt++;
			}
		}
		kCnt = 0;
		for (j = 1; j < N; j++){
			copyK(PATH[0][j-1].count, PATH[0][j].count);
			copyK(PATH[0][j-1].cost, PATH[0][j].cost);
			PATH[0][j].cost[kCnt] += PATH[0][j-1].right;
			PATH[0][j].pass[kCnt] = LEFT;
			if (PATH[0][j].x_chk == TRUE){
				moveK(PATH[0][j].count);
				moveK(PATH[0][j].cost);
				moveK(PATH[0][j].pass);
				kCnt++;
			}
		}
		kCnt = 0;
	}


	//카운트 구하는 거
	for (i = 1; i < M; i++){
		for (j = 1; j < N; j++){
			mergeK(PATH[i - 1][j].count, PATH[i][j - 1].count, PATH[i][j].count);
			if (PATH[i][j].x_chk == TRUE){
				moveK(PATH[i][j].count);
			}
		}
	}

	//가중치 구하는것
	for (i = 1; i < M; i++){
		for (j = 1; j < N; j++){
			for (k = 0; k <= K; k++){
				if ((PATH[i - 1][j].cost[k] == 0) &&  (PATH[i][j - 1].cost[k] == 0)){
					PATH[i][j].cost[k] = 0;
					continue;
				} else if (PATH[i - 1][j].cost[k] == 0){
					PATH[i][j].cost[k] = PATH[i][j - 1].cost[k] + PATH[i][j - 1].right;
					PATH[i][j].pass[k] = LEFT;
				} else if (PATH[i][j - 1].cost[k] == 0){
					PATH[i][j].cost[k] = PATH[i - 1][j].cost[k] + PATH[i - 1][j].down;
					PATH[i][j].pass[k] = UP;
				} else {
					if ((PATH[i - 1][j].cost[k] + PATH[i - 1][j].down) > (PATH[i][j - 1].cost[k] + PATH[i][j - 1].right)){
						PATH[i][j].cost[k] = PATH[i][j - 1].cost[k] + PATH[i][j - 1].right;
						PATH[i][j].pass[k] = LEFT;
					} else if ((PATH[i - 1][j].cost[k] + PATH[i - 1][j].down) < (PATH[i][j - 1].cost[k] + PATH[i][j - 1].right)){
						PATH[i][j].cost[k] = PATH[i - 1][j].cost[k] + PATH[i - 1][j].down;
						PATH[i][j].pass[k] = UP;
					} else if ((PATH[i - 1][j].cost[k] + PATH[i - 1][j].down) == (PATH[i][j - 1].cost[k] + PATH[i][j - 1].right)){
						PATH[i][j].cost[k] = PATH[i-1][j].cost[k] + PATH[i-1][j].down;
						PATH[i][j].pass[k] = LEFT;
					}
				}
			}
			//현재 인덱스의 위치가 X일 경우
			if (PATH[i][j].x_chk == TRUE){
				moveK(PATH[i][j].cost);
				moveK(PATH[i][j].pass);
			}
		}
	}
}
void moveK(int kArr[]){
	int i;
	int temp;

	for (i = K; i > 0; i--){
		temp = kArr[i];
		kArr[i] = kArr[i - 1];
		kArr[i-1] = temp;
	}
	kArr[0] = 0;
}
void copyK(int start[], int dest[]){
	int i;
	for (i = 0; i <= K; i++){
		dest[i] = start[i];
	}
}
void mergeK(int first[], int second[], int dest[]){
	int i;
	for (i = 0; i <= K; i++){
		dest[i] = first[i] + second[i];
		if (dest[i] > 100000) { dest[i] %= 100000; }
	}
}
void initData(){
	int i, j, k;

	for (i = 0; i < M; i++){
		for (j = 0; j < N; j++){
			PATH[i][j].right = 0;
			PATH[i][j].down = 0;
			PATH[i][j].x_chk = FALSE;
			for (k = 0; k <= K; k++){
				PATH[i][j].count[k] = 0;
				PATH[i][j].cost[k] = 0;
				PATH[i][j].pass[k] = 0;
			}
		}
	}
}
void printAnswer(){
	int i, j, count;
	//printf("Test Case No:%d\n", number);
	fprintf(output,"Test Case No:%d\n",number++);
	for (i = 0; i <= K; i++){
		if (PATH[M - 1][N - 1].count[i] == 0 || PATH[M - 1][N - 1].count[i] == 100000) { continue; }

		count = PATH[M - 1][N - 1].count[i];
		//printf("k:%d count:%d cost:%d\n", i, count, PATH[M - 1][N - 1].cost[i]);
		fprintf(output, "k:%d count:%d cost:%d\n", i, count, PATH[M - 1][N - 1].cost[i]);
		findPass(i);
	}
	//printf("\n");
	fprintf(output, "\n");
}
void findPass(int number){

	Pos passArray[PATH_MAX+PATH_MAX];

	int i,j;
	int cnt;
	int x = M - 1;
	int y = N - 1;
		
	passArray[0].x = M-1;
	passArray[0].y = N-1;

	for (i = 1; i < M+N-1; i++){
		if (x == 0 && y == 0){
			break;
		} 
		if (PATH[x][y].pass[number] == UP){
			if (PATH[x][y].x_chk == TRUE){
				number--;
			}
			passArray[i].x = --x;
			passArray[i].y = y;
			continue;
		} else if (PATH[x][y].pass[number] == LEFT){
			passArray[i].x = x;
			if (PATH[x][y].x_chk == TRUE){
				number--;
			}
			passArray[i].y = --y;
			continue;
		}
		
		
	}

	for (j = i-1; j >= 0; j--){
		if (j == 0){
			//printf("(%d,%d)", passArray[j].x, passArray[j].y);
			fprintf(output, "(%d,%d)", passArray[j].x, passArray[j].y);
		} else {
			//printf("(%d,%d)->", passArray[j].x, passArray[j].y);
			fprintf(output, "(%d,%d)->", passArray[j].x, passArray[j].y);
		}
	}

	for (i = 0; i < M + N - 1; i++){
		passArray[i].x = 0;
		passArray[i].y = 0;
	}

	//printf("\n");
	fprintf(output, "\n");

}