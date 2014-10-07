#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX 40
#define TRUE 1
#define FALSE 0
//=================����ü=======================
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

//===============���� ����=======================
FILE *input, *output;
StackNode *top;
char inpStr[MAX];
char postExpr[MAX];
int flag;
//--------------���� ���ÿ����Լ�-----------------
void push(char item);
char pop();
char peek();
//-------����ǥ����� ����ǥ�������--------------
int checkPriority();			//�켱������ �����ϴ��Լ�
void initString();				//����ǥ����� ����� ���ڿ� �迭�� �ʱ�ȭ ��Ű���Լ�
void inToPost();				//���� -> ���� ���� �Լ�
//-------Ʈ�� ���ÿ����Լ�--------------
TreeNode* createNode(Token newData);
void destroyNode(TreeNode* node);
void destroyTree(TreeNode* root);
void buildExprTree(char *postExpression, TreeNode **node);	//���� Ʈ�� ����
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
	
		/*������ �Է¹޾� ���������� ��ȯ ��*/

		inToPost();

		/*���� �� ���*/

		fprintf(output, "%s\n", postExpr);

		/*Ʈ�� ����*/

		buildExprTree(postExpr,&root);

		/*Ʈ�� ����*/

		result = evaluateTree(root);

		/*���� ��� ���*/
		
		if (flag == FALSE){
			fprintf(output,"%d\n", result);
		} else if(flag == TRUE){
			fprintf(output, "Error!\n");
		}

		/*������ ���ڿ� �ʱ�ȭ*/

		initString();

		/*Flag �ʱ�ȭ*/
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
		// = �� �Է¹����� �ݺ��� ����
		if (!strcmp(inpStr, "=")){
			while (top != NULL){
				postExpr[expr_Idx++] = pop();
				postExpr[expr_Idx++] = ' ';
			}
			break;
		} else if (!isdigit(inpStr[0])){// �������� ���
			//top�� ���̸� ������ push
			if (top == NULL){
				push(inpStr[0]);
			} else {
			//top�� NULL�� �ƴϰ�, ���� �Է� �����ڿ� ������ top�� �����ڿ� �켱���� ���Ͽ�
			//�ڽź��� ���ų� ���� ���� �ִٸ� ��� pop�ϰ� push
				while (top != NULL && (checkPriority(peek()) >= checkPriority(inpStr[0]))){
					postExpr[expr_Idx++] = pop();
					postExpr[expr_Idx++] = ' ';
				}
				push(inpStr[0]);
			}
		} else {						// �ǿ������� ���
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

	//' ' �������� ��ū���� ���еǾ������Ƿ� ' '�� ���� ã�ư�����!
	//' ' �� �ε����� i�� ����Ű�� ��
	for (i = last; i > -1; i--){
		if (postExpression[i] == ' '){ break; }
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
	int result = 0;
	int left = 0, right = 0;

	//����� token�� �����ڶ��
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
		//�ǿ����ڶ�� data���� �����Ѵ�.
		return root->token.data;
	}
	return result;
}