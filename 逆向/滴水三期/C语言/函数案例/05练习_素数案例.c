#include<stdio.h>

int  prime(int num)
{
	int i = 2;
	int r = 1;

	while (i < num)
	{
		if (num % i == 0)
		{
			r = 0;
			break;
		}
		i++;
	}
	return r;
}

int main()
{
	int x = prime(29);
	if (x == 1)
	{
		printf("����������");
	}
	else
	{
		printf("������������");
	}

	return 0;
}

