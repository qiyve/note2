#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>


//����ֵ���� �������������б�
//{
//  ������
// return 0��
//}
//��������
int add(int a, int b)
{
	//int sum = a + b;
	//return sum;

	return a + b;
}

void print()
{
	printf("hello world");
}

//����
void swap(int a, int b)
{
	int temp = a;
	a = b;
	b = temp;


}
int main()
{

	int a = 10;
	int b = 20;
	//��������
	int c = add(a, b);

	//printf("%d\n", c);
	//print();
	
	printf("����ǰ��\n");
	printf("a= %d\n", a);
	printf("b= %d\n", b);

	swap(a, b);
	printf("������\n");
	printf("a= %d\n", a);
	printf("b= %d\n", b);

	system("pause");
	return 0;
}