#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<time.h>



int main01()
{
	/*time_t timer = time(NULL);
	srand((size_t)timer);*/
	//������������
	srand((size_t)time(NULL));

	for (int i = 0; i < 10; i++)
	{
		//printf("%d\n", rand() % 100); //0~99  
		printf("%d\n", rand() % 51 + 50); //50~100  
	}

	system("pause");
	return 0;
}

int main()
{
	//˫ɫ�� 6������ 1-32  1������ 1-16 
	srand((unsigned int)time(NULL));//���������

	int arr[6] = { 0 };
	int value; //���������
	int	flag = 0;//�����±�
	int j = 0;

	for (int i = 0; i < 6; i++)
	{
		//��ȡ�����
		value = rand() % 32 + 1; //1~32 
		//ȥ��

		for ( j = 0; j < flag; j++)
		{
			//�ж�������ظ� �оͶ�ѭ��һ��  
			if (arr[j] == value)
			{
				i--; //(����ѭ�����һ�Σ��������µ��������
				break;
			}
		}

		if (j == flag) // �ж� ����ֵ
		{
			arr[flag] = value;
			flag++;
		}

	}

	for (int i = 0; i < 6; i++)
	{
		printf("%d ", arr[i]);
	}
	//����
	printf("+ %d\n", rand() % 16 + 1);

	system("pause");
	return 0;
}