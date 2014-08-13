#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define SMAX 2000
#define TRUE -1

typedef struct _page{
	int frame;
	int count;
	int flag;
}Page;

void initMemory(int memories[MAX],int memoryNumber);
void initMemory2(Page pages[MAX],int memNum);
int pageFaultCheck(int pageArr[MAX],int memoryNumber,int seqNum);
int PageFaultChk(Page arr[MAX],int memNum,int seqNum);
int compareLRU(Page pages[MAX],int memNum);
void createOPTseq(int sequence[SMAX],int optSeqs[SMAX],int index,int seqLength);
int OPTTT(Page pages[MAX],int optSeqs[SMAX],int memNum,int seqLength);

int main()
{
	FILE *inp = fopen("page.inp","r");
	FILE *out = fopen("page.out","w");

	int memNum;
	char newLine;
	int inpDat,i;
	int cnt = 0;
	int sequence[SMAX];
	int memories[MAX];
	Page pages[MAX];
	int optSeqs[SMAX];
	int fifocnt = 0, lrucnt = 0;
	int fifo = 0, lru = 0, opt = 0;
	int counter;


	//메모리 갯수 입력
	fscanf(inp,"%d",&memNum);

	//공백 처리
	fscanf(inp,"%c",&newLine);

	//메모리배열 -1로 초기화
	initMemory(memories,memNum);

	while(TRUE)
	{
		fscanf(inp,"%d",&inpDat);
		if(inpDat == -1)
			break;
		sequence[cnt] = inpDat;
		cnt++;
	}

	//FIFO구하는 알고리즘!!
	for(i=0;i<cnt;i++){
		if(fifocnt==memNum)
			fifocnt = 0;
		if(pageFaultCheck(memories,memNum,sequence[i]) == TRUE){
			memories[fifocnt] = sequence[i];
			fifo++;
		}else{
			continue;
		}
		fifocnt++;
	}

	//메모리배열 -1로 초기화
	initMemory2(pages,memNum);
	counter = 1;

	//LRU구하는 알고리즘시이이이작!
	for(i=0;i<cnt;i++)
	{
		if(PageFaultChk(pages,memNum,sequence[i]) == TRUE){
			//PageFault발생시 최소값의 인덱스에 시퀀스값 대입, 카운터값 대입
			pages[compareLRU(pages,memNum)].frame = sequence[i];
			pages[compareLRU(pages,memNum)].count = counter;
			lru++;
		}else{
			//시퀀스값과 같은 프레임값을 가진 인덱스에 counter값을 대입해준다
			pages[PageFaultChk(pages,memNum,sequence[i])].count = counter;
		}
		counter++;
	}

	//메모리 다시 또 초기화.
	initMemory2(pages,memNum);

	//OPT는 어떻게 해야되냐..
	for(i=0;i<cnt;i++)
	{

		if(PageFaultChk(pages,memNum,sequence[i]) == TRUE){
			//페이지폴트가 일어났을때 현재 위치에서 미래의 시퀀스 값들을 비교하기위하여
			//잔여 시퀀스를 저장하는 배열을 만든다
			createOPTseq(sequence,optSeqs,i+1,cnt);
			pages[OPTTT(pages,optSeqs,memNum,cnt-i)].frame = sequence[i];
			opt++;
		}
	}



	printf("FIFO : %d LRU : %d OPT : %d\n",fifo,lru,opt);

	fprintf(out, "FIFO: %d\n",fifo);
	fprintf(out, "LRU: %d\n",lru);
	fprintf(out, "OPT: %d\n",opt);

	fclose(inp);
	fclose(out);
	return 0;
}
void initMemory(int memories[MAX],int memoryNumber)
{
	int i;
	for(i=0;i<memoryNumber;i++)
		memories[i] = -1;
}
void initMemory2(Page pages[MAX],int memNum)
{
	int i;
	for(i=0;i<memNum;i++){
		pages[i].frame = -1;
		pages[i].count = 0;
		pages[i].flag = 0;
	}
}
int pageFaultCheck(int pageArr[MAX],int memoryNumber,int seqNum)
{
	int i;

	for(i=0;i<memoryNumber;i++)
	{
		if(pageArr[i] == seqNum)
			return i;
	}

	return TRUE;
}
int PageFaultChk(Page arr[MAX],int memNum,int seqNum)
 {
	int i;
	for(i=0;i<memNum;i++)
	{
		if(arr[i].frame == seqNum)
			return i;
	}
	return TRUE;
}
int compareLRU(Page pages[MAX],int memNum)
{
	//최소값을 찾아서 최소값 인덱스 반환
	int i;
	int index = 0;
	int min = pages[0].count;

	for(i=0;i<memNum;i++){
		if(min > pages[i].count)
		{
			min = pages[i].count;
			index = i;
		}
	}
	return index;
}
void createOPTseq(int sequence[SMAX],int optSeqs[SMAX],int index,int seqLength)
{
	int i=0;
	for(;index<seqLength;index++)
	{
		//if(sequence[index] == optSeqs[i])
		optSeqs[i++] = sequence[index]; 
	}
}
int OPTTT(Page pages[MAX],int optSeqs[SMAX],int memNum,int seqLength)
{
	int i,j;
	int max;
	int index = 0;


	//현재 메모리 배열에 저장된 프레임 들과 미래시퀀스의 값을 비교하여서
	//미래의 사용되는 거리 만큼 카운트 값을 넣는다.
	//그리고 미래의 시퀀스에 있어서 거리값을 대입시킬 수 있는 값이라면 flag 값을 1로 줌.
	for(i=0;i<memNum;i++)
	{
		for(j=0;j<seqLength;j++)
		{
			if(pages[i].frame == optSeqs[j]){
				pages[i].count = j+1;
				pages[i].flag = 1;
				break;
			}
		}
	}

	//flag값이 0이라는 것은 현재 pageFault를 야기시키는 시퀀스가
	//미래에 사용되지 않는 다는 것이므로 이값이 가장 큰 count값을 지녀야한다
	//따라서 3000이라는 큰 숫자를 대입했다.
	for(i=0;i<memNum;i++){
		if(pages[i].flag == 0){
			pages[i].count = 3000;
			break;
		}
	}

	//flag값 초기화
	for(i=0;i<memNum;i++)
		pages[i].flag = 0;
	

	//count가 최대값인 것이 가장 나중에 사용된다는 것이므로 최대값을 가진 인덱스를 찾는다.
	max = pages[0].count;
	for(i=0;i<memNum;i++)
	{
		if(max < pages[i].count){
			max = pages[i].count;
			index = i;
		}
	}

	return index;
}