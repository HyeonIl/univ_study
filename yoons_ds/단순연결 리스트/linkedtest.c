#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
	int data;
	struct _node *next;
}Node;

int main()
{
	Node* head = NULL;
	Node* tail = NULL;
	Node* curPos = NULL;

	Node* temp;
	int rData;

	//데이터의 삽입

	while(1)
	{
		printf("자연수 입력 : ");
		scanf("%d",&rData);

		if(rData<1)
			break;

		temp = (Node*)malloc(sizeof(Node));
		temp->data = rData;
		temp->next = NULL;

		if(head == NULL)
		{
			head = temp;
		}else
			tail->next = temp;

		tail = temp;
	}

	//조회

	if (head==NULL){
		puts("저장된 데이터 없음");
	}else{
		//head데이터 호출
		curPos = head;
		printf("저장된 데이터 출력 :\n%d ",curPos->data);
		
		while(curPos->next != NULL){
			curPos = curPos->next;
			printf("%d ",curPos->data);
		}
	}

	//삭제

	if (head==NULL){
		puts("저장된 데이터 없음");
	}else{
		Node *deleteNext;

		curPos = head;
		("%d 삭제",curPos->data);
		deleteNext = head->next;

		while(deleteNext->next !=NULL){

			curPos = deleteNext;
			deleteNext = curPos->next;
			free(curPos);
		}
	}

	return 0;
}