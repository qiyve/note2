#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#include<stdlib.h>

//�ڴ泣������
int main01()
{
	//�����±�Խ��
	char ch[11] = "hello world";

	char* p = (char*)malloc(sizeof(char) * 11);
	strcpy(p, "hello world");
	printf("%s\n", p);
	free(p); // err �ͷŹ����ڴ� 

	return 0;
}

int main02()
{
	//Ұָ��
	//int* p = (int*)malloc(0);
	//���ٿռ�����Ͷ�Ӧ ���Ҳ��ܳ�������
	int* p = (int*)malloc(10);
	// int* p = (int*)malloc(sizeof(int)*10); ok
	p[0] = 123;
	p[1] = 456;
	p[2] = 789;

	printf("%p\n", p);
	//*p = 100;
	printf("%d\n", *p);
	printf("%d\n", *(p+1));
	free(p);

	return 0;
}

int main03()
{
	int* p = (int*)malloc(sizeof(int) * 10);


	for (int i = 0; i < 10; i++)
	{
		//ָ����� ���ϸı�ָ�뷽�� �ͷŻ����
		*p++ = i; // *p = i;  p++;
	}

	free(p);
	//�����ռ䲻�������ͷ�
	p = NULL; 
	//��ָ���������ͷ�
	free(p);
	free(p);
	free(p);
	free(p);

	return 0;
}

void func01(int* p)
{
	p = (int*)malloc(sizeof(int) * 10);
	printf("�βΣ�%p\n", p);
}

void func02(int** p)
{
	*p = (int*)malloc(sizeof(int) * 10);
	printf("�βΣ�%p\n", *p);
}

//����ֵ
int* func03()
{
	int* p = (int*)malloc(sizeof(int) * 10);
	return p;
}

int main()
{
	int* p = NULL;
	//ֵ����
	//func01(p); err
	//��ַ����
    // func02(&p); ok
	p = func03();
	printf("ʵ�Σ�%p\n", p);

	for (int i = 0; i < 10; i++)
		p[i] = i;

	for (int i = 0; i < 10; i++)
	{
		printf("%d\n", p[i]);
	}

	free(p);

	return 0;
}