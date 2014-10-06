#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define TRUE 1
#define MAX 40
//����ü//
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

//��������
FILE *input, *output;
StackNode *top;
char inputChar;
char postExpr[MAX];
int postIndex;
//------���� ���ÿ����Լ�---------------
void push(char item);
char pop();
char peek();
//------����ǥ����� ����ǥ�������--------------
int checkPriority();			//�켱������ �����ϴ��Լ�
void initString();				//����ǥ����� ����� ���ڿ� �迭�� �ʱ�ȭ ��Ű���Լ�
void inToPost();				//���� -> ���� ���� �Լ�
//-------Ʈ�� ���ÿ����Լ�--------------
TreeNode* createNode(Token newData);
void destroyNode(TreeNode* node);
void destroyTree(TreeNode* root);
void buildExprTree(char *postExpression, TreeNode **node);	//���� Ʈ�� ����
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

		//���� ǥ��� ���
		fprintf(output, "%s\n", postExpr);

		/*Ʈ�� ����*/
		buildExprTree(postExpr, &root);
		evaluateTree(root);
		/* ���⼭ �ʱ�ȭ �� ����*/
		

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
	//���� char���� ���ڶ��..
	if (isdigit(inputChar)){
		postExpr[postIndex++] = inputChar;
	} else if (inputChar == ' '){
		if (postExpr[postIndex-1] != ' '){
			postExpr[postIndex++] = inputChar;
		}
	} else {
		//������ ó��..
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

	//' ' �������� ��ū���� ���еǾ������Ƿ� ' '�� ���� ã�ư�����!
	//' ' �� �ε����� i�� ����Ű�� ��
	for (i = last; i > -1; i--){
		if (postExpression[i] == ' '){ break;}
	}

	//����� ������ ������ ���̰� 1�̶�� �������̰ų� 1�ڸ� ����
	if (last - i == 1){
		if (isdigit(postExpression[last])){
			temp.data = postExpression[last] - '0';
		} else {
			temp.oper = postExpression[last];
		}
	} else {
		//�ƴ϶�� 2�ڸ��� �̻��� �����̰���
		//������ �ε����� i�̹Ƿ� i���������� �д´�
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