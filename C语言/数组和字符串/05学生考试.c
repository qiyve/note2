#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>

int main()
{
	//����һ������ �洢����ѧ�����ųɼ� 
	//���ÿ��ѧ�����ܳɼ� ƽ���ɼ�
	//���ÿ��ѧ�Ƶ��ܳɼ� ƽ���ɼ�
	int arr[5][3];

   //��ȡѧ���ɼ�
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			scanf("%d", &arr[i][j]);
		}
	}

	//��ӡѧ���ɼ�
	for (int i = 0; i < 5; i++)
	{
		int sum = 0;
		for (int j = 0; j < 3; j++)
		{
			sum += arr[i][j];
			//printf("%d", arr[i][j]);
		}
		printf("��%d��ѧ���ܳɼ���%d\t ƽ�ֳɼ���%d\n", i + 1, sum, sum / 3);
	}

	//ÿ���ܳɼ� ��ƽ����
	for (int i = 0; i < 3; i++)
	{
		int sum = 0;
		for (int j = 0; j < 5; j++)
		{
			sum += arr[j][i];
			
		}
		printf("��%�ŵ��ܳɼ���%d\t ƽ�ֳɼ���%d\n", i + 1, sum, sum / 3);
	}

	system("pause");
	return 0;
}