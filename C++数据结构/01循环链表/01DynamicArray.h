#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

//��̬�����ڴ棬���� ����ŵ��ڴ�ŵ��ǣ�����
//��̬���� ���5��Ԫ�� �����ڴ� �������� �ͷ��ڴ�6 ���߸����룿 
//����capacity�����ҵ�����ڴ�ռ�һ�����Դ�Ŷ���Ԫ��
//size���� ��¼��ǰ�����о����Ԫ�ظ���


typedef struct DYNAMICARRAY
{
	int* pAddr;//������ݵ�ַ
	int size; //��ǰ��С
	int capacity; //��������������ǰ��������ɶ���Ԫ��

}Dynamic_Array;

//дһϵ�е���ض� DYNAMICARRAY�ṹ������ĺ���

//��ʼ��
Dynamic_Array* Init_Array();
//����
void PushBack_Array(Dynamic_Array* arr, int value);
//����λ��ɾ��
void RemoveByPos_Array(Dynamic_Array* arr, int pos);
//����ֵɾ��
void RemoveByValue_Array(Dynamic_Array* arr, int value);
//����
int Find_Array(Dynamic_Array* arr, int value);
//��ӡ
void Print_Array(Dynamic_Array* arr);
//�ͷŶ�̬������ڴ�
void FreeSpace_Array(Dynamic_Array* arr);

//�������
void Clear_Array(Dynamic_Array* arr);
//��ȡ��̬��������
int Capacity_Array(Dynamic_Array* arr);
//��ȡ��̬���鵱ǰԪ�ظ���
int Size_Array(Dynamic_Array* arr);
//����λ�û�ȡĳ��λ�õ�Ԫ��
int At_Array(Dynamic_Array* arr, int pos);





#endif 
