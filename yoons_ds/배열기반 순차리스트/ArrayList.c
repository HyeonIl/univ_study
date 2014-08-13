#include <stdio.h>
#include "ArrayList.h"

void ListInit(List * plist)
{
	plist->numOfData = 0; //데이터 값 0으로 초기화
	plist->curPosition = -1; //현재 포지션값 -1로 초기화
}


void LInsert(List * plist,LData data)
{
	if(plist->numOfData > LIST_LEN)	// MAX값 보다 numofdata가 높다면ㄴ
	{
		puts("저장불가!");
		return;
	}

	plist->arr[plist->numOfData] = data;	//입력된 data값을 numOfdata값을 인덱스로 하여서 배열에 저장
	(plist->numOfData)++;					//numOfdata값을 1 증가
}

int LFirst(List *plist, LData * pdata){
	
	if(plist->numOfData==0)		//데이터가 하나도 없다면 탐색이 무쓸모지..
	return FALSE;

	plist->curPosition = 0;		//curPos를 0으로 인덱싱해줌
	*pdata = plist->arr[0];		//인덱스 0에 해당하는 값을 pdata에 저장

	return TRUE;
}


int LNext(List * plist, LData * pdata){

	if(plist ->curPosition >= plist->numOfData-1){	//배열의 MAX값인 numOfData보다 크거나 같으면 
	return FALSE;									//FALSE를 리턴하는 이유는 이전값을 인덱싱 하므로.. ++시킬 값이
	}												//존재하지 않는 다는 뜻이다.

	(plist->curPosition)++;		//curPos값을 +1해주어서 그다음 값을 탐색하도록 함
	*pdata = plist->arr[plist->curPosition];	//curPos를 인덱스로 하는 배열의 값을 pdata에 저장

	return TRUE;
}

LData LRemove(List * plist){
	int rpos =  plist->curPosition;
	int i;

	LData rdata = plist->arr[rpos];

	for(i=rpos;i<(plist->numOfData)-1;i++)
		plist->arr[i] = plist->arr[i+1];

	plist->curPosition--;			//인덱스값을 -1  왜냐면 데이터를 지움으로 뒤의 데이터가 하나씩 당겨지므로 인덱스 값을
									//당겨주어야 한다. 그래야 LNext에서 ++해서 다음값을 가르킬 때 정상적인 값을 가르킴
	plist->numOfData--;				//데이터값을 -1

	return rdata;
}

int LCount(List * plist)
{
	return plist->numOfData;
}