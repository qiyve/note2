#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int main01()
{
	//while (���ʽ)

	int i = 0;
	//��ѭ��
	while (i<10)
	{
		printf("%d\n", i);
		i++;
	}

	return 0;
}

int main02()
{
	//��ӡ0��100��ż��
	int i = 0;
	while (i<100)
	{
		if (i % 2 == 0)
		{
			printf("%d\n", i);
		}
		i++;
	}

	return 0;
}
int main()
{
	//��������Ϸ
	//100���ڷ�����7 ���ܱ�7�ı�����ӡ������
	int i = 0;

	while (i<100)
	{
		//     7�ı���     ��λ��7       ʮλ��7
		if (i % 7 == 0 || i % 10 == 7 || i / 10 == 7)
		{
		
			printf("������\n");
		
		}
		else
		{
			printf("%d\n", i);
		}

		i++;

	}
}