#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>	



int main01()
{

	float a = 3.14f;
	double b = 3.14;

	printf("%.2f\n", a);
	printf("%f\n", b);

	//sizeof �ֽڴ�С
	//���������� �洢���ڴ��еĸ�ʽ��Ϊ������λ ָ��λ С��λ
	printf("%d\n", sizeof(a));
	printf("%d\n", sizeof(b));

	return 0;
}

int main02()
{
	int a = 10;
	float b = 3.14;

	//ռλ�� %p ��ʾ���һ��������Ӧ���ڴ��ַ��ţ��޷���ʮ���������Σ� 
	printf("%p\n", &a);
	printf("%p\n", &b);

	//��С�˶���
	getchar();
	return 0;
}

int main()
{
	//��ѧ������ e����10 
	
	//float a = 3210.456; 
	//float a = 0.123452;
	//printf("%e\n", a);

	float b = 3.2e3f;
	printf("%f\n", b);

	return 0;
}