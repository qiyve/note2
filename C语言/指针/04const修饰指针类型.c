#include <stdio.h>



int main01()
{
	//����
	const int a = 10;
	//a = 100;// ��
	//ָ�����޸ĳ�����ֵ
	int* p = &a;
	*p = 100;
	printf("%d\n", a);

	system("pause");
	return 0;
}

int main02()
{
	int a = 10;
	int b = 20;

	// const int* p = &a;  const ����ָ������
	// �����޸�ָ�������ֵ��ָ��ָ�򣩣��������޸�ָ��ָ���ڴ�ռ��ֵ��ָ��ָ���ֵ��
	const int* p = &a;
	
	//p = &b; //ok
	//*p = 100;��

	printf("%d\n", *p);

	system("pause");
	return 0;
}

int main03()
{
	int a = 10;
	int b = 20;

	//int* const p = &a   const����ָ�����
	// �����޸�ָ��ָ���ڴ�ռ��ֵ��ָ��ָ���ֵ�����������޸�ָ�������ֵ��ָ��ָ��
	int* const p = &a;
	//p = &b; ��
	*p = 200;
	printf("%d\n", a);

	system("pause");
	return 0;
}

int main()
{
	int a = 10;
	int b = 20;
	//const int* const p = &a; ������ָ������ ������ָ�����
	const int* const p = &a;
	//�������ö���ָ��������޸�
	int** p1 = &p;
	//*p1 = &b;
	**p1 = 100;
	printf("%d\n", *p);

	//p = &b; ����
	//*p = 100; ����

	system("pause");
	return 0;
}