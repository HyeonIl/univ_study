#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX 40
#define TRUE 1
#define FALSE 0
//=================구조체=======================
typedef struct token{
	char oper;
	int data;
}Token;
typedef struct stackNode{
	char data;
	struct stackNode *link;
}StackNode;
typedef struct treeNode{
	Token token;
	struct treeNode *left;
	struct treeNode *right;
}TreeNode;

//===============전역 변수=======================
FILE *input, *output;
StackNode *top;
char inpStr[MAX];
char postExpr[MAX];
int flag;
//--------------스택 관련연산함수-----------------
void push(char item);
char pop();
char peek();
//-------중위표기식을 후위표기식으로--------------
int checkPriority();			//우선순위를 결정하는함수
void initString();				//후위표기식이 저장된 문자열 배열을 초기화 시키는함수
void inToPost();				//중위 -> 후위 로직 함수
//-------트리 관련연산함수--------------
TreeNode* createNode(Token newData);
void destroyNode(TreeNode* node);
void destroyTree(TreeNode* root);
void buildExprTree(char *postExpression, TreeNode **node);	//수식 트리 생성
int evaluateTree(TreeNode *root);
//---------------------------------------------
int main()
{
	TreeNode *root = NULL;
	int testCase;
	char newLine;
	int result;

	input = fopen("expression.inp", "r");
	output = fopen("expression.out", "w");
	flag = FALSE;

	fscanf(input, "%d%c", &testCase, &newLine);

	while (testCase--){
	
		/*중위를 입력받아 후위식으로 변환 함*/

		inToPost();

		/*후위 식 출력*/

		fprintf(output, "%s\n", postExpr);

		/*트리 생성*/

		buildExprTree(postExpr,&root);

		/*트리 연산*/

		result = evaluateTree(root);

		/*연산 결과 출력*/
		
		if (flag == FALSE){
			fprintf(output,"%d\n", result);
		} else if(flag == TRUE){
			fprintf(output, "Error!\n");
		}

		/*후위식 문자열 초기화*/

		initString();

		/*Flag 초기화*/
		flag = FALSE;
		
	}//end testCase while

	fclose(input);
	fclose(output);
	return 0;
}
//----------------------------------------------------
void push(char item)
{
	StackNode *temp = (StackNode*)malloc(sizeof(StackNode));
	temp->data = item;
	temp->link = top;
	top = temp;
}
char pop()
{
	char item;
	StackNode *temp = top;

	if (top == NULL){
		return 0;
	} else {
		item = temp->data;
		top = temp->link;
		free(temp);
		return item;
	}
}
char peek()
{
	char item;
	StackNode *temp = top;

	if (top == NULL){
		return 0;
	} else {
		item = temp->data;
		return item;
	}
}
//-----------------------------------------------------
int checkPriority(char operand){
	switch (operand){
		case '+':
		case '-':
			return 2;
		case '*':
		case '/':
		case '%':
			return 3;
	}
	return -1;
}
void inToPost()
{
	int i;
	int length;
	int expr_Idx = 0;

	while (TRUE){
		fscanf(input, "%s", inpStr);
		// = 을 입력받으면 반복문 정지
		if (!strcmp(inpStr, "=")){
			while (top != NULL){
				postExpr[expr_Idx++] = pop();
				postExpr[expr_Idx++] = ' ';
			}
			break;
		} else if (!isdigit(inpStr[0])){// 연산자일 경우
			//top이 널이면 무조건 push
			if (top == NULL){
				push(inpStr[0]);
			} else {
			//top이 NULL이 아니고, 현재 입력 연산자와 스택의 top의 연산자와 우선순위 비교하여
			//자신보다 같거나 높은 것이 있다면 모두 pop하고 push
				while (top != NULL && (checkPriority(peek()) >= checkPriority(inpStr[0]))){
					postExpr[expr_Idx++] = pop();
					postExpr[expr_Idx++] = ' ';
				}
				push(inpStr[0]);
			}
		} else {						// 피연산자일 경우
			length = strlen(inpStr);
			for (i = 0; i < length; i++){
				postExpr[expr_Idx++] = inpStr[i];
			}
			postExpr[expr_Idx++] = ' ';
		}
	}
	postExpr[expr_Idx - 1] = 0;
}
void initString(){
	int i;
	for (i = 0; i < MAX; i++){
		postExpr[i] = 0;
	}
}
//-----------------------------------------------------
TreeNode* createNode(Token newData){
	TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->token = newData;

	return newNode;
}
void destroyNode(TreeNode* node)
{
	free(node);
}
void destroyTree(TreeNode* root)
{
	if (root == NULL)
		return;
	destroyTree(root->left);
	destroyTree(root->right);
	destroyNode(root);
}
//-----------------------------------------------------
void buildExprTree(char *postExpression, TreeNode **node)
{
	int length = strlen(postExpression);
	int last = length - 1;
	int i, j;
	char str[10] = { 0 };
	int str_cnt = 0;

	//char temp = postExpression[last];
	Token temp = { 0, 0 };

	//' ' 공백으로 토큰들이 구분되어있으므로 ' '을 향해 찾아가보자!
	//' ' 의 인덱스를 i가 가르키게 됨
	for (i = last; i > -1; i--){
		if (postExpression[i] == ' '){ break; }
	}

	//공백과 마지막 문자의 차이가 1이라면 연산자이거나 1자리 숫자
	if (last - i == 1){
		if (isdigit(postExpression[last])){
			temp.data = postExpression[last] - '0';
		} else {
			temp.oper = postExpression[last];
		}
	} else {
		//아니라면 2자릿수 이상의 숫자이겟지
		//공백의 인덱스가 i이므로 i다음번부터 읽는다
		for (j = i + 1; j < length; j++){
			str[str_cnt++] = postExpression[j];
		}
		temp.data = atoi(str);
	}
	if (i >= 0){
		postExpression[i] = '\0';
	}

	if (temp.data == 0){
		*node = createNode(temp);
		buildExprTree(postExpression, &(*node)->right);
		buildExprTree(postExpression, &(*node)->left);
	} else {
		*node = createNode(temp);
	}
}
int evaluateTree(TreeNode *root)
{
	int result = 0;
	int left = 0, right = 0;

	//노드의 token이 연산자라면
	if (root->token.oper != 0){
		left = evaluateTree(root->left);
		right = evaluateTree(root->right);
		switch (root->token.oper){
		case '+':
			result = left + right;
			break;
		case '-':
			result = left - right;
			break;
		case '*':
			result = left * right;
			break;
		case '%':
			if (right == 0) {
				flag = TRUE;
				return 0;
			}
			result = left % right;
			break;
		case '/':
			if (right == 0) {
				flag = TRUE;
				return 0;
			}
			result = left / right;
			break;
		}
	} else {
		//피연산자라면 data값을 리턴한다.
		return root->token.data;
	}
	return result;
}