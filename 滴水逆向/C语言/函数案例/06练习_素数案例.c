#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int prime(int num)
{

	int i = 2;
	int  r;

	if (num >= i)
	{
		while (num)
		{
			if (num % i == 0)
			{
				r = 0; //����
				break;
			}
			else
			{
				r = 1; //��
				break;
			}
			i++;
			
		}
	}
	else
	{
		r = 1; //Ϊ1ʱ
	}
	return r;
}

int main()
{
	//��ȡ
	int n;
	scanf("%d", &n);

	if (prime(n))
	{
		printf("����Ϊ����\n");
	}
	else
	{
		printf("������������\n");
	}

	
	return 0;
}
