#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<time.h>

//��������
//extern int add(int a, int b);
//int add(int a, int b);
int add(int, int);

int main()
{
	
	//��������
	add(10, 20);
	int a = add(10, 20);
	printf("%d\n", a);

	system("pause");
	return 0;
}

//�������� ֻ�ܶ���һ��
int add(int a,int b)
{
	return a + b;
}