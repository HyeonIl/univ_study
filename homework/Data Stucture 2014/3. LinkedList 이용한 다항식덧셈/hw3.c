#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _poly
{
	int coef;
	int expo;
	struct _poly *next;
}PolyNode;
void insertNode(PolyNode **head, int coef, int expo);
int main()
{
	FILE *inp = fopen("hw3.inp","r");
	FILE *out = fopen("hw3.out","w");
	PolyNode *head = NULL;
	PolyNode *secHead = NULL;
	PolyNode *pA,*pB,*delPre;
	PolyNode *firPoly = NULL;
	PolyNode *secPoly = NULL;
	PolyNode *resultPoly = NULL;

	int i;
	int inpCoef,inpExpo;
	char test;
	char command[10];

	//첫번째 식 입력받음
	for(i=0;i<10;i++){
		fscanf(inp,"%d %d%c",&inpCoef,&inpExpo,&test);
		insertNode(&head,inpCoef,inpExpo);
		if(test == 10)
			break;
	}

	//명령어 입력받음
	fscanf(inp,"%s",command);

	if(!strcmp(command,"INSERT"))
	{
		//일단 비교대상 식 입력받음
		for(i=0;i<10;i++){
			fscanf(inp,"%d %d%c",&inpCoef,&inpExpo,&test);
			insertNode(&secHead,inpCoef,inpExpo);
			if(test == 10)
				break;
		}
		pA = head;
		pB = secHead;

		while(pA && pB){
			//첫번째 식과 두번째 식의 지수가 같을 경우;
			if(pA->expo == pB->expo){
				insertNode(&firPoly,pA->coef,pA->expo);
				pA = pA->next;
				pB = pB->next;
				//첫번째 식과 두번째 식의 지수가 다를 경우;
			}else if(pA->expo < pB->expo){
				insertNode(&firPoly,pB->coef,pB->expo);
				pB = pB->next;
			}else if(pA->expo > pB->expo){
				insertNode(&firPoly,pA->coef,pA->expo);
				pA = pA->next;
			}
		}
		for(;pA!=NULL;pA=pA->next)
			insertNode(&firPoly,pA->coef,pA->expo);
		for(;pB!=NULL;pB=pB->next)
			insertNode(&firPoly,pB->coef,pB->expo);

	}else{

		//일단 비교대상 식 입력받음
		for(i=0;i<10;i++){
			fscanf(inp,"%d %d%c",&inpCoef,&inpExpo,&test);
			insertNode(&secHead,inpCoef,inpExpo);
			if(test == 10)
				break;
		}
		pA = head;
		pB = secHead;

		while(pA != NULL && pB != NULL){
			//pA가 가르키는 지수와 pB의 지수가 같을때 삭제 연산을 수행한다.
			if(pA->expo == pB->expo){
				if(pA == head){
					head = pA->next;
					pA = head;
					pB = pB->next;
				}else{
					delPre = head;
					while(delPre->next != NULL){
						if(delPre->next == pA){
							break;
						}
						delPre = delPre->next;
					}
					delPre->next = pA->next;
					pA = delPre->next;
				}
			}else if(pA->expo < pB->expo){
				pB = pB->next;
			}else if(pA->expo > pB->expo)
				pA = pA->next;
		}
		firPoly = head;
	}

	head = NULL;
	secHead = NULL;

	//두번째식 입력받음
	for(i=0;i<10;i++){
		fscanf(inp,"%d %d%c",&inpCoef,&inpExpo,&test);
		insertNode(&head,inpCoef,inpExpo);
		if(test == 10)
			break;
	}

	//명령어 입력받음
	fscanf(inp,"%s",command);

	if(!strcmp(command,"INSERT"))
	{
		//일단 비교대상 식 입력받음
		for(i=0;i<10;i++){
			fscanf(inp,"%d %d%c",&inpCoef,&inpExpo,&test);
			insertNode(&secHead,inpCoef,inpExpo);
			if(test == 10)
				break;
		}
		pA = head;
		pB = secHead;

		while(pA && pB){
			//첫번째 식과 두번째 식의 지수가 같을 경우;
			if(pA->expo == pB->expo){
				insertNode(&secPoly,pA->coef,pA->expo);
				pA = pA->next;
				pB = pB->next;
				//첫번째 식과 두번째 식의 지수가 다를 경우;
			}else if(pA->expo < pB->expo){
				insertNode(&secPoly,pB->coef,pB->expo);
				pB = pB->next;
			}else if(pA->expo > pB->expo){
				insertNode(&secPoly,pA->coef,pA->expo);
				pA = pA->next;
			}
		}
		for(;pA!=NULL;pA=pA->next)
			insertNode(&secPoly,pA->coef,pA->expo);
		for(;pB!=NULL;pB=pB->next)
			insertNode(&secPoly,pB->coef,pB->expo);

	}else{
		//일단 비교대상 식 입력받음
		for(i=0;i<10;i++){
			fscanf(inp,"%d %d%c",&inpCoef,&inpExpo,&test);
			insertNode(&secHead,inpCoef,inpExpo);
			if(test == 10)
				break;
		}
		pA = head;
		pB = secHead;

		while(pA != NULL && pB != NULL){
			//pA가 가르키는 지수와 pB의 지수가 같을때 삭제 연산을 수행한다.
			if(pA->expo == pB->expo){
				if(pA == head){
					head = pA->next;
					pA = head;
					pB = pB->next;
				}else{
					delPre = head;
					while(delPre->next != NULL){
						if(delPre->next == pA){
							break;
						}
						delPre = delPre->next;
					}
					delPre->next = pA->next;
					pA = delPre->next;
				}
			}else if(pA->expo < pB->expo){
				pB = pB->next;
			}else if(pA->expo > pB->expo)
				pA = pA->next;
		}
		secPoly = head;
	}

	//이제 덧셈을 수행할 차례군... 흐흐

	pA = firPoly;
	pB = secPoly;

	while(pA && pB)
	{
		if(pA->expo == pB->expo){
			insertNode(&resultPoly,(pA->coef)+(pB->coef),pA->expo);
			pA = pA->next; pB = pB->next;
		}else if(pA->expo > pB->expo){
			insertNode(&resultPoly,pA->coef,pA->expo);
			pA = pA->next;
		}else{
			insertNode(&resultPoly,pB->coef,pB->expo);
			pB = pB->next;
		}
	}
	for(;pA!=NULL;pA = pA->next)
		insertNode(&resultPoly,pA->coef,pA->expo);
	for(;pB!=NULL;pB = pB->next)
		insertNode(&resultPoly,pB->coef,pB->expo);

	pA = resultPoly;

	while(pA){
		if(pA->coef == 0){
			if(pA == resultPoly){
				resultPoly = pA->next;
				pA = head;
			}else{
				delPre = resultPoly;
				while(delPre->next != NULL){
					if(delPre->next == pA){
						break;
					}
					delPre = delPre->next;
				}
				delPre->next = pA->next;
				pA = delPre->next;
			}
		}else
			pA = pA->next;
	}

	pA = resultPoly;

	for(;pA!=NULL;pA = pA->next){
		if(pA->coef == 0)
			continue;
		if(pA->next !=NULL){
			fprintf(out,"%d %d ",pA->coef,pA->expo);
		}else
			fprintf(out,"%d %d",pA->coef,pA->expo);
	}

	fprintf(out,"\n*");


	fclose(inp);
	fclose(out);
	return 0;
}

void insertNode(PolyNode **head, int coef, int expo)
{
	PolyNode *cur;
	PolyNode *newNode = (PolyNode*)malloc(sizeof(PolyNode));

	newNode->coef = coef;
	newNode->expo = expo;
	newNode->next = NULL;

	//head포인터가 NULL을 가르키는 경우 리스트가 존재하지 않는것이다
	if(*head == NULL){
		*head = newNode;			//head가 newNode를 가르키게 한다.
		return;
	}else{
		cur = *head;				//cur포인터가 head를 가르키게 한다음
		while(cur->next != NULL)
			cur = cur->next;	//현재리스트의 마지막 노드를 찾는다.
		cur->next = newNode;	//마지막노드에 newNode 연결
	}
}