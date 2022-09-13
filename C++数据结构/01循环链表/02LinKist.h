#ifndef LINKLIST_h
#define LINKLIST_h
#include<stdio.h>

//����ڵ�
typedef struct LINKNODE
{
	void* data;//ָ���κ����͵�����
	struct LINKNODE* next;
}LinkNode;

//����ṹ��
typedef struct LINKLIST
{
	LinkNode* head;
	int size;
	//�������������ڴ棬û����������
}LinkList;

//��ӡ����ָ��
typedef void(PRINTLINKNODE)(void*);

//��ʼ������
LinkList* Init_LinkList();
//ָ��λ�ò���
void Insert_LinkList(LinkList* list, int pos, void* data);
//ɾ��ָ��λ�õ�ֵ
void RemoveByPos_LinkList(LinkList* list, int pos);
//���������
int Size_LinkList(LinkList* list);
//����
int Find_LinkList(LinkList* list, void* data);
//��ӡ������
void Preint_LinkList(LinkList* list, PRINTLINKNODE print);
//���ص�һ�����
void* Front_LinkList(LinkList* list);
//�ͷ�������ڴ�
void FreeSpace_LinkList(LinkList* list);


#endif 
