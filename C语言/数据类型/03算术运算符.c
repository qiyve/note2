#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>	

int main01()
{
	//0������Ϊ����
	int a = 10;
	int b = 3;
	//����������������������  
	printf("%d\n", a / b);
	//ȡģ ������ ֻ�ܶ����β���
	printf("%d\n", a % b);


	return 0;
}

int main02()
{
	int a = 10;
	//a = a + 1;
	//a++; //������ �ڱ��ʽ����� �ڽ���++ 
	//++a; //ǰ���� �ڱ��ʽ����ǰ �Ƚ���++
	//int b = ++a * 10;
	int b = a++ * 10;

	printf("%d\n", b);
	printf("%d\n", a);

 
	return 0;
}

int main()
{
	int a = 10;
	a--;

	printf("%d\n",a);

	return;
}