#include <stdio.h>
#include "ArrayList.h"
#include "NameCard.h"

int main()
{
	List list;
	NameCard *newCard;
	int i;
	ListInit(&list);

	//1. 3명의 전화번호 정보를, 앞서 우리가 구현한 리스트에 저장한다.
	newCard = MakeNameCard("조현일","01065429759");
	LInsert(&list,newCard);
	newCard = MakeNameCard("김민서","01044450324");
	LInsert(&list,newCard);
	newCard = MakeNameCard("김태윤","01088350650");
	LInsert(&list,newCard);

	
	//2. 특정 이름을 대상으로 탐색을 진행하여, 그 사람의 정보를 출력한다.
	puts("=======[조현일]을 대상으로 탐색=======\n");

	if(LFirst(&list,&newCard)){
		if(!NameCompare(newCard,"조현일"))
			ShowNameCardInfo(newCard);
		while(LNext(&list,&newCard))
			if(!NameCompare(newCard,"조현일"))
				ShowNameCardInfo(newCard);
	}

	//3. 특정 이름을 대상으로 탐색을 진행하여, 그 사람의 전화번호 정보를 변경한다.

	puts("=======[김태윤]를 대상으로 탐색=======\n");

	if(LFirst(&list,&newCard)){
		if(!NameCompare(newCard,"김태윤"))
			ChangePhone(newCard,"01044449999");
		while(LNext(&list,&newCard))
			if(!NameCompare(newCard,"김태윤"))
				ChangePhone(newCard,"01044449999");

		puts("전화번호를 01044449999로 변경완료!\n");
	}


	//4. 특정 이름을 대상으로 탐색을 진행하여, 그 사람의 정보를 삭제한다.

	puts("=======[김민서]를 대상으로 탐색=======\n");

	if(LFirst(&list,&newCard)){
		if(!NameCompare(newCard,"김민서"))
			LRemove(&list);
		while(LNext(&list,&newCard))
			if(!NameCompare(newCard,"김민서"))
				LRemove(&list);

		puts("데이터 삭제완료!\n");
	}
	
	//5. 끝으로 남아있는 모든 사람의 전화번호 정보를 출력한다.

	puts("---남아있는 모든 사람의 전화번호 출력----\n");
	
	if(LFirst(&list,&newCard)){
		ShowNameCardInfo(newCard);

		while(LNext(&list,&newCard))
		ShowNameCardInfo(newCard);
	}

	return 0;
}