#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>	


int main()
{
	/*int num1;
	int num2;
	int num3;
	printf("������С��A������:\n");
	scanf("%d", &num1);
	printf("������С��B������:\n");
	scanf("%d", &num2);
	printf("������С��C������:\n");
	scanf("%d", &num3);*/

	int A, B, C;
	printf("��������ֻС�������:\n");
	scanf("%d%d%d", &A,&B,&C);

	if (A>B)
	{
		if (A > C)
		{
			//a>c
			printf("С��A����\n");
		}
		else
		{
			//c<a
			printf("С��C����\n");
		}
		
	}
	else  //a<b
	{
		if (B >C)
		{
			//b>c
			printf("С��B����\n");
		}
		else
		{
			//c>b
			printf("С��C����\n");
		}
	}



	system("pause");
	return 0;
}