#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define TRUE 1
#define MAX 40
//구조체//
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

//전역변수
FILE *input, *output;
StackNode *top;
char inputChar;
char postExpr[MAX];
int postIndex;
//------스택 관련연산함수---------------
void push(char item);
char pop();
char peek();
//------중위표기식을 후위표기식으로--------------
int checkPriority();			//우선순위를 결정하는함수
void initString();				//후위표기식이 저장된 문자열 배열을 초기화 시키는함수
void inToPost();				//중위 -> 후위 로직 함수
//-------트리 관련연산함수--------------
TreeNode* createNode(Token newData);
void destroyNode(TreeNode* node);
void destroyTree(TreeNode* root);
void buildExprTree(char *postExpression, TreeNode **node);	//수식 트리 생성
int evaluateTree(TreeNode *root);
//--------------------------------------
int main()
{
	TreeNode *root = NULL;
	int testCase;
	char temp;
	postIndex = 0;

	input = fopen("expression.inp", "r");
	output = fopen("expression.out", "w");

	fscanf(input, "%d%c", &testCase, &temp);

	while (testCase--){
		while (TRUE){
			fscanf(input, "%c", &inputChar);
			if (inputChar == '\n'){
				continue;
			}
			if (inputChar == '=') {
				while (top != NULL){
					if (postExpr[postIndex-1] != ' '){
						postExpr[postIndex++] = ' ';
					} 
					postExpr[postIndex++] = pop();
				}
				break;
			} else {
				inToPost();
			}//end if
		}//end input while

		//후위 표기식 출력
		fprintf(output, "%s\n", postExpr);

		/*트리 생성*/
		buildExprTree(postExpr, &root);
		evaluateTree(root);
		/* 여기서 초기화 를 진행*/
		

		postIndex = 0;
		
		initString();

	}//end testCase while

	

	fclose(input);
	fclose(output);
	return 0;
}
//-----------------------------------------
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
		return;
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
		return;
	} else {
		item = temp->data;
		return item;
	}
}
//------------------------------------------
void initString(){
	int i;
	for (i = 0; i < MAX; i++){
		postExpr[i] = 0;
	}
}
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
	//읽은 char값이 숫자라면..
	if (isdigit(inputChar)){
		postExpr[postIndex++] = inputChar;
	} else if (inputChar == ' '){
		if (postExpr[postIndex-1] != ' '){
			postExpr[postIndex++] = inputChar;
		}
	} else {
		//연산자 처리..
		if (top == NULL){
			push(inputChar);
		} else{
			while (top != NULL && (checkPriority(peek()) >= checkPriority(inputChar))){
				postExpr[postIndex++] = pop();
			}
			push(inputChar);
		}
	}
}
//------------------------------------------
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
//------------------------------------------
void buildExprTree(char *postExpression, TreeNode **node)
{
	int length = strlen(postExpression);
	int last = length - 1;
	int i,j;
	char str[10] = {0};
	int str_cnt = 0;

	//char temp = postExpression[last];
	Token temp = {0,0};

	//' ' 공백으로 토큰들이 구분되어있으므로 ' '을 향해 찾아가보자!
	//' ' 의 인덱스를 i가 가르키게 됨
	for (i = last; i > -1; i--){
		if (postExpression[i] == ' '){ break;}
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

}