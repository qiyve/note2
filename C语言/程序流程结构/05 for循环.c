#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>


int main01()
{
	int j = 0;
	for (int i = 0; i < 10, j < 10; i++, j += 5)
	{
		
		printf("%d\n", i);
	
	}
	return 0;
}
int main02()
{
	int i = 0;

	//��ѭ�� while(1) for(;;)
	for (;;)
	{
		//if (i >= 10)
		//{
		//	//����ѭ��
		//	break;
		//}
		printf("%d\n", i);
		i++;
	}

	return 0;
}
int main()
{
	//������
	//ͨ���������һ��1-100֮�����

	//���������
	//1����������� time.h  stdlib.h
	//2��������������
	//3����ȡ�����
	srand((unsigned int)time(NULL));//ÿ���������һ��

	//int value = rand() % 10; //0~9
	//for (int i = 0; i < 10; i++)
	//{
	//	int value = rand() % 10; //0~9
	//	printf("%d\n", value);
	//}
	int value = rand() % 100; //0~99
	int num;
	for(;;)
	{
		printf("���������֣�\n");
		scanf("%d", &num);

		if (value > num)
		{
			printf("����ֵ��С\n");
		}
		else if ( value < num)
		{
			printf("����ֵ����\n");
		}
		else
		{
			printf("��ϲ��¶���\n");
			break;
		}
		
	}

	system("pause");
	return 0;
}