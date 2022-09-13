#ifndef CIRCLELINKLIST
#define CIRCLELINKLIST

//��д�������ṹ�������API����
#define CIRCLELINKLIST_TRUE 1
#define CIRCLELINKLIST_FALST 0

#include<stdio.h>
#include<stdlib.h>

//����С���
typedef struct CIRCLELINKNODE 
{
	struct CIRCLELINKNODE* next;
}CircleLinkNode;

//����ṹ��
typedef struct CIRCLELINKLIST {

	CircleLinkNode head;
	int size;

}CircleLinkList;;

//�Ƚϻص�
typedef int(*COMPARENODE)(CircleLinkNode*, CircleLinkNode*);
//��ӡ�ص�
typedef void (*PRINTNODE)(CircleLinkNode*);

//��д�������ṹ�������API����
#define CIRCLELINKLIST_TRUE 1
#define CIRCLELINKLIST_FALST 0

//��ʼ������
CircleLinkList* Init_CircleLinkList();
//���뺯��
void insert_CircleLinkList(CircleLinkList* clist, int pos, CircleLinkNode* data);
//��õ�һ��Ԫ��
CircleLinkNode* Frond_CircleLinkList(CircleLinkList* clist);
//����λ��ɾ��
void RemovePos_CircleLinkList(CircleLinkList* clist,int pos);
//����ֵɾ��
void RemoveByValue_CircleLinkList(CircleLinkList* clist, CircleLinkNode* data, COMPARENODE compare);
//���������
int Size_CircleLinkList(CircleLinkList* clist);
//�ж��Ƿ�Ϊ��
int IsEmpty_CiecleLinkList(CircleLinkList* clist);
//����
int Find_CircleLinkList(CircleLinkList* clist, CircleLinkNode* data, COMPARENODE compare);
//��ӡ���
void Print_CircleLinkList(CircleLinkList* clist, PRINTNODE print);
//�ͷ��ڴ���
void FreeSpace_CircleLinkList(CircleLinkList* clist);



#endif 