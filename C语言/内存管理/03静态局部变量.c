#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#include<stdlib.h>


void func1()
{
	//��̬�ֲ�����ֻ���ʼ��һ�� ���Զ�θ�ֵ
	static int b = 10;
	b++;
	printf("%d\n", b);

}

int main()
{
	//��̬�ֲ�����
	//static int b = 10;
	//printf("%d\n", b);

	for (int i = 0; i < 10; i++)
	{
		func1();
	}
	
	return 0;
}