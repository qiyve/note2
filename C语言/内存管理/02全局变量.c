#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#include<stdlib.h>

//������   ȫ�ֱ������Ժ;ֲ���������
//ȫ�ֱ��� �ں����ⲿ����ı���
//������������Ŀ�������ļ�  ��� �������ļ���ʹ�� ��Ҫ����  extern
//�������ڣ��ӳ��򴴽�����������
int a = 10;
void func1()
{
	a = 100;
	printf("%d\n", a);

}

int main()
{
	//�����ڲ���ʱ����þͽ�ԭ��
	int a = 123;
	printf("%d\n", a);
	printf("%p\n", &a);
	//�����ڲ�����
	{
		int a = 456;
		//a = 456;
		printf("%d\n", a);
		printf("%p\n", &a);

	}
	printf("%d\n", a);

	func1();
	
	return 0;
}