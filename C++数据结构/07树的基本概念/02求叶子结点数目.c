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

int num = 0;
void CaculateLeafNum(BinaryNode* root,int* leafNum)
{
	if (root == NULL)
	{
		return;
	}
	if (root->lchild == NULL && root->rchild == NULL)
	{
		(*leafNum)++; //leafNum �Ǹ�ָ��
	}

	//������Ҷ�ӽ�����Ŀ
	CaculateLeafNum(root->lchild, leafNum);
	//������Ҷ�ӽڵ����Ŀ
	CaculateLeafNum(root->rchild, leafNum);

}

void CresteBinaryTree()
{
	//�������
	BinaryNode node1 = { 'A',NULL,NULL };
	BinaryNode node2 = { 'B',NULL,NULL };
	BinaryNode node3 = { 'C',NULL,NULL };
	BinaryNode node4 = { 'D',NULL,NULL };
	BinaryNode node5 = { 'E',NULL,NULL };
	BinaryNode node6 = { 'F',NULL,NULL };
	BinaryNode node7 = { 'G',NULL,NULL };
	BinaryNode node8 = { 'H',NULL,NULL };
	

	//��������ϵ
	node1.lchild = &node2;
	node1.rchild = &node6;
	node2.rchild = &node3;
	node3.lchild = &node4;
	node3.rchild = &node5;
	node6.rchild = &node7;
	node7.lchild = &node8;


	int leafNum = 0;
	CaculateLeafNum(&node1, &leafNum);
	printf("Ҷ�ӽ�����Ŀ%d\n", leafNum);
}

int main()
{
	CresteBinaryTree();
	
	system("pause");
	return 0;
}