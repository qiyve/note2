#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#include<stdlib.h>

//δ��ʼ��ȫ�ֱ���
int a1;
//��ʼ��ȫ�ֱ���
int b1 = 10;
//δ��ʼ����̬ȫ�ֱ���
static int c1;
//��ʼ����̬ȫ�ֱ���
static int d1 = 20;

int main()
{
	int e1 = 10;
	//δ��ʼ���ľ�̬�ֲ�����
	static int f1;
	//��ʼ���ľ�̬�ֲ�����
	static int h1 = 30;

	//�ַ�������
	char* p = "hello world";
	//����
	int arr[] = { 1,2,3,4, };
	//ָ��
	int* pp = arr;

	printf("δ��ʼ��ȫ�ֱ�����%p\n", &a1);
	printf("��ʼ��ȫ�ֱ�����%p\n", &b1);
	printf("δ��ʼ����̬ȫ�ֱ�����%p\n", &c1);
	printf("��ʼ����̬ȫ�ֱ�����%p\n", &d1);
	printf("��ʼ���ֲ�������%p\n", &e1);
	printf("δ��ʼ���ľ�̬�ֲ�������%p\n", &f1);
	printf("��ʼ���ľ�̬�ֲ�������%p\n", &h1);
	printf("�ַ���������%p\n", p);
	printf("���飺%p\n", arr);
	printf("ָ�������%p\n", pp);
	printf("ָ���ַ��%p\n", &pp);


	return 0;
}