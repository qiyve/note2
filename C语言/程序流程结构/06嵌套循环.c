#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

int main01()
{
	//���ִ��һ��  �ڲ�ִ��һ��
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			printf("i = %d, j = %d\n", i, j);
		}
		printf("\n");
	}

	system("pause");
	return 0;
}

int main02()
{
	//ģ��ʱ��
	//ʱ��
	for (int i = 0; i < 24; i++)
	{
		//����
		for (int j = 0; j < 60; j++)
		{
			//����
			for (int k = 0; k < 60; k++)
			{
				system("cls");
				printf("%02d:%02d:%02d:\n", i, j, k);
				Sleep(960); //ִ�е��� ����һ��
			}
		}
		
	}

	return 0;
}
int main()
{
	//�žų˷��ھ�
	/*
	 1 * 1 = 1
	 2 * 1 = 1  2 * 1 = 2
	 3 * 1 = 1  3 * 2 = 6  3 * 3 = 9
	 */
	for (int i = 1; i <= 9; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			printf("%d*%d=%d\t", i, j,i*j);
		}
		printf("\n");
	}

	system("pause");
	return 0;
}