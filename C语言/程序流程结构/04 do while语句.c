#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>


int main01()
{
	
	int i = 0;

	do 
	{
		printf("%d\n", i);
		i++;
	} while (i < 10);
	

	//while (i)
	//{
	//	printf("%d\n", i);
	//	i++;
	//}
}
int main()
{
	//ˮ�ɻ�  ��100��999 ����λ�������� ��ӵ�������������Ϊˮ�ɻ���

	int i = 100;
	do
	{
		//��λ
		int a = i % 10;
		//ʮλ
		int b = i / 10 % 10;
		//��λ
		int c = i / 100;

		if (a * a * a + b * b * b + c * c * c == i)
		{
			printf("%d\n", i);
		}
		i++;

	} while (i <= 999);

	return 0;
}