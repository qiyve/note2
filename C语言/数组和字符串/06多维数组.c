#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>

int main01()
{   
	//һά���飺
	//�������� ������[Ԫ�ظ���]
	//��ά���飺
	// �������� ������[��][��]
	
	//��ά����
	//�������� ������[��][��][��]

	int arr[2][3][4] =
	{
	   {
		   {1,2,3,4},
		   {2,3,4,5},
		   {3,4,5,6},
	   },
		{
			{4,5,6,7},
			{5,6,7,8},
			{6,7,8,9},
		}
	};
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				printf("%d ", arr[i][j][k]);
			}
			printf("\n");
		}
		printf("\n");
	}
	
	printf("��ά�����С��%d\n", sizeof(arr));// 2*3*4*4 ��*��*��*sizeof(��������)
	printf("��ά����һ���С��%d\n", sizeof(arr[0]));
	printf("��ά����һ�д�С��%d\n", sizeof(arr[0][0]));
	printf("��ά����һԪ�ش�С��%d\n", sizeof(arr[0][0][0]));


	printf("������%d\n", sizeof(arr)/sizeof(arr[0]));
	printf("������%d\n", sizeof(arr[0]) / sizeof(arr[0][0]));
	printf("������%d\n", sizeof(arr[0][0]) / sizeof(arr[0][0][0]));



	system("pause");
	return 0;
}

int main()
{
	int arr[2][3][4][5] = { 1,2,3 };
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				for (int l = 0; l < 5; l++)
				{
					printf("%d ", arr[i][j][k][l]);
				}
				printf("\n");
			}
			printf("\n");
		}
		
	}


	system("pause");
	return 0;
}