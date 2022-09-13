#ifndef SEQQUEUE_H
#define SEQQUEUE_H

#define MAX_SIZE 1024
#include<stdio.h>
#include<stdio.h>

//˳����нṹ��
typedef struct SEQQUEUE {

	void* data[MAX_SIZE];
	int size;
}SeqQueue;

//��ʼ��
SeqQueue* Init_SeqQueue();
//���
void Push_SeqQueue(SeqQueue* queue, void* data);
//���ض�ͷԪ��
void* Front_SeqQueue(SeqQueue* queue);
//����
void Pop_SeqQueue(SeqQueue* queue);
//���ض�βԪ��
void* Back_SeqQueue(SeqQueue* queue);
//���ش�С
int Size_SeqQueue(SeqQueue* queue);
//���
void Clear_SeqQueue(SeqQueue* queue);
//����
void FreeSpace_SeqQueue(SeqQueue* queue);


#endif 