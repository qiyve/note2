#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#include<stdlib.h>

int main01()
{
	//atoi()��ɨ��nptr�ַ���������ǰ��Ŀ��ַ���ֱ���������ֻ������Ųſ�ʼ��ת����
	//	���������ֻ��ַ�����������'\0'���Ž���ת���������������

	char ch[] = "  -12345-6";
	int i = atoi(ch);

	printf("%d\n", i);

	return 0;
}

int main02()
{

	char ch[] = "  -12.345-6";
	double i = atof(ch);

	printf("%.2f\n", i);

	return 0;
}

int main()
{
	char ch[] = "   125488- 6123";
	long i = atol(ch);

	printf("%ld\n", i);

	return 0;
}