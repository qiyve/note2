#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define SIZE 10
int main()
{
	//ʮֻС�������
	//��������
	int arr[SIZE];
	
	//��ȡС������
	for (int i = 0; i < SIZE; i++)
	{
		scanf("%d", &arr[i]);
	}
	
	//�Ƚ����� ����һ�����ֵ����
	//int max = 0; 
	int max = arr[0];

	for (int i = 1; i < SIZE; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}

	printf("���ص�С������Ϊ��%d\n", max);

	return 0;

}