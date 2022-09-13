#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//���������
typedef struct BINARYNODE {
	char ch;//��
	struct BINARYNODE* lchild; //��
	struct BINARYNODE* rchild; //��
}BinaryNode;

void Recursion(BinaryNode* root)
{
	if (root == NULL)
	{
		return;
	}
	printf("%c", root->ch);
	Recursion(root->lchild);
	Recursion(root->rchild);
}

BinaryNode* CreateBinaryTree()
{
	fflush(stdin); //����ļ�������
	char ch;
	scanf("%c", &ch);

	//������
	BinaryNode* node;
	//BinaryNode* lchild;
	//BinaryNode* rchild;


	if (ch == '#')
	{
		node = NULL;
	}

	else
	{
	/*	lchild = CreatBinaryTree();
		rchild = CreatBinaryTree();*/

		//�������
		node = (BinaryNode*)malloc(sizeof(BinaryNode));
		node->ch = ch;
		node->lchild = CreateBinaryTree();
		node->rchild = CreateBinaryTree();
	}

	return node;
}


int main()
{
	//������
	BinaryNode* root = CreateBinaryTree();
	//��ӡ��
	Recursion(root);
	
	system("pause");
	return 0;
}