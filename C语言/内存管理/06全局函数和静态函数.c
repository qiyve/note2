#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#include<stdlib.h>

// �������Ե����Լ�  ��Ϊ�ݹ麯��
void print()
{
	printf("hello world\n");

}

int main01()
{
	//ȫ�ֺ�������������������Ψһ��
	//��������������Ŀ��������ʹ��
	print();
	
	return 0;
}

//��̬����
static void func2()
{
	printf("hello world\n");

}

int main()
{
	func2();

	return 0;
}