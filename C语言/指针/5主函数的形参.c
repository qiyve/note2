#include <stdio.h>


int main01()
{
	const int a = 10;
	//a = 100; err
	//ͨ��һ��ָ�����޸ı�����ֵ
	int* p = &a;
	*p = 100;




	system("pause");
	return 0;
}

int main02()
{
	char ch1[] = "hello";
	char ch2[] = "world";

	//ָ������ָ��
	//�����޸�ָ�������ֵ��ָ��deָ�򣩣� �������޸�ָ�����ָ���ڴ��ֵ��ָ��ָ���ֵ��
	const char* p = ch1;
	// *p = 'm'; err
	//p[2] = 'm'; // *(p+2)= 'm' // err 
	//p = ch2;  //ok



	system("pause");
	return 0;
}

int main03()
{

	char ch1[] = "hello";
	char ch2[] = "world";

	//����ָ��
	//�����޸�ָ�����ָ���ڴ�ռ��ֵ��ָ��ָ���ֵ��
	//�������޸�ָ�������ֵ ��ָ���ָ��
	char* const p = ch1;
	//p = ch2; err
	*p = 'w'; // ok  // ch[0]
	*(p + 2) = 'w';//ok 

	printf("%s\n", p);
	printf("%s\n", ch1);

	return 0;
}

int main()
{
	char ch1[] = "hello";
	char ch2[] = "world";

	//const������ָ��ָ�� ������ָ��ָ���ֵ
	//ָ���ָ���ָ��ָ��ֵ���������޸�  ֻ��
	const char* const p = ch1;

	// *p = ch2;  err
	// *p = 'w';  err

	char** p1 = &p;

	//*p1 = ch2;
	*(*p1 + 1) = 'm';

	printf("%s\n", p);

	return 0;
}