#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>


//�ڴ�����
int main01()
{
	//����
	int* p = (int*)malloc(sizeof(int) * 10);

	//memset(void* s,int c,size_t n) �����ڴ�ռ��ֵ 
	//����1����Ҫ�����ڴ��׵�ַ ����2�����õ�ֵ�� ����3����Ҫ���õĴ�С���ֽڴ�С��
	memset(p, 0, sizeof(int)*10);  //һ���ڴ�ռ�����Ϊ0����Ч�� �����Ͳ�̫׼ȷ
	//memset(p, 1, sizeof(int) * 10); err
	for (int i = 0; i < 10; i++)
	{
		printf("%d\n", p[i]);
	}

	//�ַ�
	char ch[10];
	//memset(ch, 'A', sizeof(char) * 10); err
	memset(ch, 0, sizeof(char) * 10); 
	printf("%s\n", ch);

	return 0;
}

//�ڴ濽��
int main02()
{

	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 ,10};
	int* p = (int*)malloc(sizeof(int) * 10);

	//�ַ������� strcpy()
	//�ڴ濽�� memcpy()

	memcpy(p, arr, sizeof(int) * 10);

	for (int i = 0; i < 10; i++)
	{
		printf("%d\n", p[i]);
	}
	free(p); //�ͷ��ڴ�


	char ch[] = "hello \0world";
	char str[100];
	//�ַ�����������\0ֹͣ
	//strcpy(str, ch);

	//�ڴ濽�� �������ݺ��ֽ��й�
	memcpy(str, ch, 13);
	printf("%s\n", str);
	for (int i = 0; i < 13; i++)
	{
		printf("%c", str[i]);
	}

	int arr0[] = { 1,2,3,4,5,6,7,8,9,10 };
	//���������Ŀ���Դ�����ص� ���ܻᱨ��
	memcpy(&arr[5], &arr[3], 20);
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", arr[i]);
	}
	return 0;
}

int main()
{
	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	//���������Ŀ���Դ�����ص� ���ܻᱨ��
	//memcpy(&arr[5], &arr[3], 20);

	//��������ص���memmove
	memmove(&arr[5], &arr[3], 20);
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", arr[i]);
	}

	return 0;
}

//�ڴ�Ƚ�
int main04()
{

	//int arr1[] = { 1,2,3,4,5,6,7,8,9 };
	//int arr2[] = { 1,2,3,4,5 };

	char arr1[] = "hello\0 world";
	char arr2[] = "hello\0 world";
	//strcmp();

	int value = memcmp(arr1, arr2, 13);

	printf("%d\n", value);

	return 0;
}

