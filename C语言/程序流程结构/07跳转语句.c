#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

//break
int main01()
{
	for (int i = 0; i<10 ; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (j == 6)//j=6 �˳��ڲ�ѭ��
			{
				break;
			}
			printf("%d %d\n", i, j);
		}
		printf("\n");
	}


	system("pause");
	return 0;
}

//continue �÷�
int main02()
{    
	//��ӡż����
	for (int i = 0; i < 20; i++)
	{
		if (i % 2 == 1)
		{
			//��ֹ����ѭ������ִ���´�ѭ�� 
			continue;
		}
		printf("%d\n", i);
	}

	system("pause");
	return 0;
}

//goto
int main03()
{
	printf("hello world 1\n");
	printf("hello world 2\n");

	goto FLAG1;
	printf("hello world 3\n");
	printf("hello world 4\n");


	system("pause");
	return 0;

FLAG1: //�˴��� ð�� ��
	printf("hello world 5\n");

	return 1;
}

int main04()
{
	int i = 0, j = 0;


	for ( i = 0; i < 10; i++)
	{
		if (i == 5)
		{
			goto FLAG2;
		}
		printf("i=%d\n", i);
	}

	//j��Ҫ����ʼֵ ��Ϊ��ֱ����ת������
	for (j = 0; j < 10; j++)
	{
		FLAG2:
		printf("j=%d\n", j);
		
	}
	system("pause");
	return 0;
}

//α����
int main()
{
FLAG:
	
	printf("hello world\n");
	goto FLAG;

	return 0;
}