#include<iostream>
using namespace std;
#include<string>

//�������� (�º���)

/*
 1.����������ʹ�ã���������ͨ�����������ã������в����������з���ֵ
 2.�������󳬳���ͨ�����ĸ����������������Լ���״̬
 3.�������������Ϊ��������
*/


class MyAdd
{
public:
	int operator()(int v1,int v2)
	{
		return v1 + v2;
	}
};

//1.����������ʹ�ã���������ͨ�����������ã������в����������з���ֵ
void test01()
{
	MyAdd myadd;
	cout << myadd(10, 20) << endl;
}

//2.�������󳬳���ͨ�����ĸ����������������Լ���״̬
class MyPrint
{
public:

	MyPrint()
	{
		this->count = 0;//��ʼΪ0 
	}

	void operator()(string test)
	{
		cout << test << endl;
		count++; //��¼���ô���
	}

	int count; //�ڲ��Լ�״̬
};

void test02()
{
	MyPrint myprint;
	myprint("hello world");
	myprint("hello world");

	cout << "myprint ���ô���:" << myprint.count << endl;
}

void doPrint(MyPrint& mp, string test)
{
	mp(test);
}

//3.�������������Ϊ��������
void test03()
{
	MyPrint myprint;
	doPrint(myprint, "hello C++");

}

int main()
{
	//test01();

	//test02();

	test03();

	system("pause");
	return 0;
}