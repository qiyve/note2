#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>


int main01()
{
	//�����ַ���Ч����

	char ch[] = "hello world";
	printf("�����С��%d\n",sizeof(ch));
	printf("�ַ������ȣ�%d", strlen(ch));

	system("pause");
	return 0;
}

int main()
{
	char ch[] = "hello world";
	int len = 0;

	while (ch[len]!='\0')
	{
		len++;
	}

	printf("�ַ������ȣ�%d", len);

	system("pause");
	return 0;
}