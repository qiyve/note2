#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>

//��ά����

int main01()
{
	//��������  ������[��][��]
	// {
	//  {ֵ1��ֵ2}��
	//  {ֵ3��ֵ4}
	// }
	int arr[2][3] =
	{
		{1,2,3},
		{4,5,6}
	};

	//arr[1][2] = 20;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}

	printf("�����С��%d\n", sizeof(arr));//���� * ���� * sizeof(�������ͣ�
	printf("����һ�д�С��%d\n", sizeof(arr[0]));
	printf("����Ԫ�ش�С��%d\n", sizeof(arr[0][0]));

	printf("����������%d\n", sizeof(arr) / sizeof(arr[0]));
	printf("����������%d\n", sizeof(arr[0]) / sizeof(arr[0][0]));


	system("pause");
	return 0;
}

int main02()
{
	int arr[2][3] =
	{
		{1,2,3},
		{4,5,6}
	};

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%p\n", &arr[i][j]);
		}

	}
	//��ά�����׵�ַ
	//printf("%p\n", arr);
	//printf("%p\n", arr[0]);
	////arr[0] = 100; ���� ����һ������
	//printf("%p\n", &arr[0][0]);
	//printf("%p\n", &arr[0][1]);

	//printf("%p\n", arr[1]);

	system("pause");
	return 0;
}

int main()
{
	//int arr[2][3] = { {1,2,3},{4,5,6} };
	//int arr[2][3] = { 1,2,3,4,5,6 };
	int arr[][3] = { 1,2,3,4,5,6,7 };

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}

	system("pause");
	return 0;
}