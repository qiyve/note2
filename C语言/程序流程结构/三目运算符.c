#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MAX(a,b) (a)>(b)?(a):(b)

int main()
{
	int a = 20;
	int b = 30;
	printf("���ֵΪ��%d\n", MAX(a, b));

	return 0;
}


int main01()
{
	int a = 10;
	int b = 20;
	int c = 30;
	//��ʾ1 �����ʽ2:���ʽ3
	//c = a > b ? a : b;
	//printf("���ֵΪ��%d\n", c);

	printf("���ֵΪ��%d\n", a > b ? a : b);

	printf("���ֵΪ��%d\n", a > b ? (a > c ? a : c) : (b > c ? b : c));
	//if (a > b)
	//{
	//	printf("a��\n");
	//}
	//else
	//{
	//	printf("b��\n");
	//}



	system("pause");
	return 0;
}