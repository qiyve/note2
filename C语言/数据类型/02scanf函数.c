#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>	


int main01()
{
	/*char ch;

	scanf("%c", &ch);
	putchar(ch);*/
	
	int a, b;
	scanf("%d,%d", &a, &b);
	printf("%d\t%d", a, b);

	system("pause");
	return 0;
}

int main()
{

	char ch;

	//���ռ��� ��ȡ�ַ�
	ch = getchar();
	putchar(ch);

	//��ʱͣ������
	getchar();
	return 0;
}