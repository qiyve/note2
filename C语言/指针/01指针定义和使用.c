#include <stdio.h>

int main01()
{
	int a = 0xaabbccdd;
	//a = 100;
	printf("%p\n", &a);
	

	system("pause");
	return 0;
}
int main02()
{
	//����ָ������洢������ַ
	int a = 10;
	//ָ������  -> ��������* 
	int* p;
	p = &a;
	//ͨ��ָ���Ӹı������ֵ
	*p = 100;
	printf("%p\n", p);
	printf("%p\n", &a);

	printf("%d\n", a);
	printf("%d\n", *p);
	
	system("pause");
	return 0;
}

int main03()
{
	//&��ȡ��ַ��������ά�ȵ�
	//*��ȡֵ�����ǽ�ά�ȵ�

	char ch = 'a';
	char* p = &ch;
	//printf("%d\n", sizeof(char*));
	//int a = 10;
	//int* p = &a;
	//printf("%d\n", sizeof(int*));

	//ָ�����ڴ���ռ���ֽڴ�С
	//��32Ϊ����ϵͳ������ָ��������4���ֽڴ�С
	//��64Ϊ����ϵͳ������ָ��������8���ֽڴ�С
	printf("%d\n", sizeof(char*));
	printf("%d\n", sizeof(int*)); 
	printf("%d\n", sizeof(short*));
	printf("%d\n", sizeof(long*));
	printf("%d\n", sizeof(long long*));
	printf("%d\n", sizeof(float*));
	printf("%d\n", sizeof(double*));

	system("pause");
	return 0;
}

int main()
{
	//�ڶ���ָ������һ��Ҫ�ͱ��������Ͷ�Ӧ��
	char ch = 97;

	int* p = &ch;
	//*p = 123;

	printf("%d\n", *p);
	printf("%d\n", ch);


	/*printf("%p\n", p);
	printf("%p\n", &ch);*/


	system("pause");
	return 0;
}