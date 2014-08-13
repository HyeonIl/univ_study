#include <stdio.h>
#include <stdlib.h>
#define TRUE 1

typedef struct _treeNode{
	int data;
	struct _treeNode *leftNode;
	struct _treeNode *rightNode;
}TreeNode;

//출력용 전역변수 count
int count = 0;

//함수
TreeNode* insertNode(TreeNode *p,int data);
void InOrder(TreeNode *root,FILE *output);
void PostOrder(TreeNode *root,FILE *output);
TreeNode* searchNode(TreeNode* root, int data);
void searchPrintNode(TreeNode* root, int data,FILE* output);
int deleteNode(TreeNode *root, int data,FILE* output);
int main()
{
	int inpDat;
	char test = 0;
	char command;
	TreeNode *root = NULL;

	//전역변수
	FILE *inp = fopen("hw6.inp","r");
	FILE *out = fopen("hw6.out","w");

	//루트노드 생성
	fscanf(inp,"%d",&inpDat);
	root = insertNode(root,inpDat);

	//데이터를 받아와서 노드 생성
	while(test != 10){
		fscanf(inp,"%d%c",&inpDat,&test);
		insertNode(root,inpDat);
	}
	//중위순회 하면서 출력
	InOrder(root,out);
	fprintf(out,"\n");

	//파일의 끝을 가르킬때 까지 while문 실행
	while(feof(inp) == 0){
		fscanf(inp,"%c %d%c",&command,&inpDat,&test);
		//명령어가 D이면 삭제연산
		if(command == 'D'){
			count = 0;
			if(deleteNode(root,inpDat,out) == 0){
				fprintf(out,"error(no entry)\n");
			}else{
				PostOrder(root,out);
				fprintf(out,"\n");
			}
		}else if(command == 'S'){
			//S이면 탐색연산
			searchPrintNode(root,inpDat,out);
		}
	}

	fclose(inp);
	fclose(out);
	return 0;
}
TreeNode* insertNode(TreeNode *p,int data)
{
	TreeNode *newNode;

	//p가 가르키는 값이 루트노드이다
	//NULL이면 생성해야겟지?
	if(p == NULL)
	{
		newNode = (TreeNode*)malloc(sizeof(TreeNode));
		newNode->data = data;
		newNode->leftNode = NULL;
		newNode->rightNode = NULL;
		return newNode;
	}else if(data < p->data){
		p->leftNode = insertNode(p->leftNode,data);
	}else if(data > p->data){
		p->rightNode = insertNode(p->rightNode,data);
	}

	return p;
}
void InOrder(TreeNode *root,FILE *output)
{
	if(root){
		InOrder(root->leftNode,output);
		if(count == 0){
			fprintf(output,"%d",root->data);
			count++;
		}else
			fprintf(output," %d",root->data);
		InOrder(root->rightNode,output);
	}
}
void PostOrder(TreeNode *root,FILE *output)
{
	if(root){
		PostOrder(root->leftNode,output);
		PostOrder(root->rightNode,output);
		if(count == 0){
			fprintf(output,"%d",root->data);
			count++;
		}else
			fprintf(output," %d",root->data);
	}
}
TreeNode* searchNode(TreeNode* root, int data)
{
	TreeNode* p;
	p = root;
	while(p != NULL){
		if(data < p->data){
			p=p->leftNode;
		}else if(data == p->data){
			return p;
		}else
			p=p->rightNode;
	}
	return p;
}
void searchPrintNode(TreeNode* root, int data,FILE* output)
{
	TreeNode* p;
	p = root;
	while(p != NULL){
		if(data < p->data){
			fprintf(output,"%d ",p->data);
			p = p->leftNode;
		}else if(data == p->data){
			fprintf(output,"%d\n",p->data);
			return;
		}else{
			fprintf(output,"%d ",p->data);
			p=p->rightNode;
		}
	}
	fprintf(output,"error(no entry)\n");
	//return p;
}
int deleteNode(TreeNode *root, int data,FILE* output)
{
	TreeNode *parent, *p, *child;
	TreeNode *lsucc_parent, *lsucc;
	TreeNode *rsucc_parent, *rsucc;
	int leftdiff;
	int rightdiff;

	parent = NULL;
	p = root;

	//삭제할 노드 위치 탐색
	while((p != NULL) && (p->data != data)){
		parent = p;
		if(data < p->data)
			p = p->leftNode;
		else
			p = p->rightNode;
	}
	//삭제할 노드가 없으면
	if(p == NULL){
		//fprintf(output,"error(no entry)\n");
		return 0;
	}

	//삭제할 노드가 터미널 노드 이면
	if((p->leftNode == NULL) && (p->rightNode == NULL)){
		if(parent != NULL){
			//부모의 왼쪽노드가 삭제노드라면 왼쪽노드를 NULL시킨다
			if(parent->leftNode == p)
				parent->leftNode = NULL;
			else
				parent->rightNode = NULL;
		}
		root = NULL;
	}//삭제할 노드의 자식노드가 1개인 경우
	else if((p->leftNode == NULL) || (p->rightNode == NULL)){
		//삭제할 노드의 왼쪽 노드가 NULL이면 오른쪽에 자식노드가 존재한다는 의미이다
		//따라서 오른쪽의 노드값을 child변수에 저장
		if(p->leftNode == NULL)
			child = p->rightNode;
		else
			child = p->leftNode;

		if(parent != NULL){
			if(parent->leftNode == p)
				parent->leftNode = child;
			else
				parent->rightNode = child;
		}else
			root = child;
	}else{
		//삭제할 노드가 두 개의 자식 노드를 가진 경우
		lsucc_parent = p;
		lsucc = p->leftNode;
		rsucc_parent = p;
		rsucc = p->rightNode;

		//왼쪽서브트리의 최대값 탐색
		while(lsucc ->rightNode != NULL){
			lsucc_parent = lsucc;
			lsucc = lsucc->rightNode;
		}
		//오른쪽서브트리의 최소값 탐색
		while(rsucc -> leftNode != NULL){
			rsucc_parent = rsucc;
			rsucc = rsucc->leftNode;
		}

		//최대값,최소값과 삭제노드의 차이를 비교한다.
		leftdiff = (p->data - lsucc->data);
		rightdiff = (rsucc->data - p->data);

		//왼쪽서브트리의 최대값이 더 비슷한 값일때
		if(rightdiff > leftdiff){
			if(lsucc_parent->leftNode == lsucc)
				lsucc_parent->leftNode = lsucc->leftNode;
			else
				lsucc_parent->rightNode = lsucc->leftNode;

			p->data = lsucc->data;
			p=lsucc;
		}else{
			if(rsucc_parent->leftNode == rsucc)
				rsucc_parent->leftNode = rsucc->rightNode;
			else
				rsucc_parent->rightNode = rsucc->rightNode;
			p->data = rsucc->data;
			p=rsucc;
		}
	}

	free(p);
	return 1;
}