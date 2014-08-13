#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TRUE 1

typedef struct _stackNode
{
	char data;
	struct _stackNode *next;
}StackNode;

//스택의 top 노드를 가르키는 포인터
StackNode *top;
//함수선언
void push(char item);
char pop();
char peek();
int main()
{
	FILE *inp = fopen("hw4.inp","r");
	FILE *out = fopen("hw4.out","w");

	char inpChar = NULL;

	while(TRUE)
	{
		fscanf(inp,"%c",&inpChar);
		//공백문자를 만나면 스택안의 것 모두 출력시킴
		if(inpChar == '\n'){
			while(top != NULL){
				fprintf(out,"%c",pop());
			}
			fprintf(out,"\n");
			//그다음 문자를 확인한다.
			fscanf(inp,"%c",&inpChar);
			//'*'인지 확인하고 맞다면 프로그램종료
			if(inpChar == '*'){
				fprintf(out,"*");				
				break;
			}
		}

		//현재입력받은 문자가 숫자라면 그대로 출력
		if(isdigit(inpChar)){
			fprintf(out,"%c",inpChar);
		}else if(inpChar == '('){
			//여는 괄호를 만나면 push함
			push(inpChar);
		}else if(inpChar == ')'){
			//닫는 괄호를 만나면 여는괄호 전까지 모두 pop시킴;
			while(top != NULL && top->data != '('){
				fprintf(out,"%c",pop());
			}
			//그리고 여는괄호를 pop시켜서 괄호를 출력시키지 않도록 한다.
			pop();
		}else{
			//연산자 처리
			//스택은 우선순위가 높은 순서대로 쌓인다
			if(inpChar == '*' || inpChar == '/'){
				//스택안의 연산자 우선순위가 같으면 스택안의 원소를 pop시키고 push한다
				if(top == NULL){
					push(inpChar);
				}else{
					if(peek() == '*' || peek() == '/'){
						while(top != NULL && top->data != '('){
							fprintf(out,"%c",pop());
						}
					}
					push(inpChar);
				}
			}else{
				//아니라면 + - 를 처리해야겟지
				if(top == NULL){
					push(inpChar);
				}else{
					// + 와 - 는 우선순위가 낮으므로 스택에 모두 pop시키고 push한다.
					while(top != NULL && top->data != '('){
						fprintf(out,"%c",pop());
					}
					push(inpChar);
				}
			}
		}
	}//end While

	fclose(inp);
	fclose(out);
}
void push(char item)
{
	StackNode *temp = (StackNode*)malloc(sizeof(StackNode));
	temp->data = item;
	temp->next = top;
	top = temp;
}
char pop()
{
	char item;
	StackNode *temp = top;

	//스택이 공백리스트 이면
	if(top == NULL)
		return 0;
	else{
		item = temp->data;
		top = temp->next;
		free(temp);
		return item;
	}
}
char peek()
{
	char item;
	if(top == NULL)
		return 0;
	else{
		item = top->data;
		return item;
	}
}
