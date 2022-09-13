#ifndef SEQSTACK_H
#define SEQSTACK_H
#include<stdio.h>
#include<stdio.h>

//����ȥģ��ջ��˳��洢
#define MAX_SIZE 1024
#define SEQSTACK_TRUE 1
#define SEQSTACK_FLAST 0


typedef struct SEQSTACK {

	void* data[MAX_SIZE];
	int size;
}SeqStack;

//��ʼ��ջ
SeqStack* Init_SeqStack();
//��ջ
void Push_SeqStack(SeqStack* stack, void* data);
//����ջ��Ԫ��
void* Top_SeqStack(SeqStack* stack);
//��ս
void Pop_SeqStack(SeqStack* stack);
//�ж��Ƿ�Ϊ��
int IsEmpty(SeqStack* stack);
//����ջ�е�Ԫ�ظ���
int Size_SeqStack(SeqStack* stack);
//�ͷ�
void FreeSpace(SeqStack* stack);


#endif 