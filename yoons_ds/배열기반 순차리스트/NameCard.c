#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NameCard.h"

// NameCard 구조체 변수의 동적 할당 및 초기화 후 주소 값 반화
NameCard* MakeNameCard(char* name, char* phone)
{
	NameCard* pCard = (NameCard*)malloc(sizeof(NameCard));
	strcpy(pCard->name,name);
	strcpy(pCard->phone,phone);

	return pCard;
}

// NameCard 구조체 변수의 정보 출력
void ShowNameCardInfo(NameCard * pcard)
{
	printf("이름 : %s\n",pcard->name);
	printf("전화번호 : %s\n\n",pcard->phone);
}

// 이름이 같으면 0, 다르면 0이 아닌 값 반환
int NameCompare(NameCard* pcard, char* name)
{
	if(!strcmp(pcard->name,name))			//strcmp를 이용하여 문자열이 같으면 0을 반환하기떄문에 !연산으로 반전
		return 0;							//따라서 같으면 0반환
	return -1;
}


// 전화번호 정보를 변경
void ChangePhone(NameCard* pcard, char* phone)
{
	strcpy(pcard->phone,phone);				//strcpy함수 이용하여 phone 값을 이용하여 구조체 변수에 대입
}