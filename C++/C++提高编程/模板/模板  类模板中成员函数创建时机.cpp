#include<iostream>
using namespace std;
#include<string>
//  ��ģ���г�Ա��������ʱ��
//  ��ģ���г�Ա��������ͨ���г�Ա��������ʱ����������ģ�

//1. ��ͨ���еĳ�Ա����һ��ʼ�Ϳ��Դ���
//2. ��ģ���еĳ�Ա�����ڵ���ʱ�Ŵ���

//�ܽ᣺ ��ģ���еĳ�Ա����������һ��ʼ�ʹ����ģ��ڵ���ʱ��ȥ����

class Person1
{
public:

	void showPerson1()
	{
		cout << "Person1 show" << endl;
	}
};

class Person2
{
public:

	void showPerson1()
	{
		cout << "Person2 show" << endl;
	}
};

template<class T>
class myCalss
{
public:

	T ojb;

	//��ģ���еĳ�Ա����
	void func1()
	{
		ojb.showPerson1();
	}
	void func2()
	{
		ojb.showPerson2();
	}
};

void test01()
{
	myCalss<Person1>m;
	m.func1();
	//m.func2();

}

int main()
{
	test01();

	
	
	system("pause");
	return 0;
}