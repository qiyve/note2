//#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>	
#pragma warning (disable:4996)

int main(void)
{
	//���ͱ���
	int a = 10;
	//������
	short b = 20;

	//������
	long c = 30;
	//��������
	long long d = 40;

	printf("%d\n", a);
	//ռλ�� %hd ��ʾ���һ��������
	printf("%hd\n", b);
	//ռλ�� %ld ��ʾ���һ��������
	printf("%ld\n", c);
	//ռλ��%lld ��ʾ���һ����������
	printf("%lld\n", d);

	//sizeof ���������������ڴ���ռ���ֽڣ�BYTE����С
	//sizeof(��������)  sizeof(������)  sizeof ������
	unsigned int len = sizeof(int);

	//printf("%d\n", len);
	printf("���Σ�%d\n", sizeof(a));
	printf("�����Σ�%d\n", sizeof(b));
	printf("�����Σ� % d\n", sizeof(c));
	printf("�������Σ�%d\n", sizeof(d));

	return 0;
}

