#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#include<stdlib.h>

//Ϊ��ʼ����ȫ�ֱ���
//int abc;
//δ��ʼ���ľ�̬ȫ�ֱ���
//static int abc;

int main()
{
	//int abc;
	static int abc;
	//�ֲ�����δ��ʼ�� ֵΪ����
	printf("%d\n", abc);
	
	
	return 0;
}