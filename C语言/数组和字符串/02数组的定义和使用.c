#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define SIZE 5

int main01()
{
	//�����һ
	//int arr[5] = { 1,2,3,4,5 };
	//int arr[] = { 1,2,3,4,5 };
	//int arr[10] = { 0 };
	//int arr[10] = { 1 };//Ĭ��0����
	int arr[10];
	arr[0] = 1;

	for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
	{
		printf("%d\n", arr[i]);
	}

	system("pause");
	return 0;
}
int main02()
{
	//int i = 10;
	//����Ԫ�ر����ǳ��� �������ʽ
	//int arr[i]; ����
	//�������Ԥ��֪����С ��̬���� -�����ٿռ�
	int arr[SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		scanf("%d", &arr[i]);
	}

	for (int i = 0; i < SIZE; i++)
	{
		printf("%d\n", arr[i]);
	}

	system("pause");
	return 0;
}
int main()
{
	int arr[5] = { 1,2,3,4,5};

	//�±�Խ�� ����ʱ�쳣 
	printf("%d\n", arr[-1]);
	printf("%d\n", arr[5]);
	for (int i = 0; i < 10; i++)
	{
		printf("%d\n", arr[i]);
	}

	return 0;

}