#include<iostream>
using namespace std;


//��̳��﷨

//��������
class Baese1
{
public:

	Baese1()
	{
		m_A = 100;
	}
	int m_A;
};

class Baese2
{
public:

	Baese2()
	{
		m_A = 200;
	}
	int m_A;
};

//���� ��Ҫ�̳�Baese1��Baese2
//�﷨�� class ���� ���̳з�ʽ  ���࣬�̳з�ʽ  ����2 ...
class Son:public Baese1,public Baese2
{
public:
	Son()
	{
		m_C = 300;
		m_D = 400;
	}
	int m_C;
	int m_D;
};

void test01()
{
	Son s;
	cout << "Son��ռ�ڴ棺" << sizeof(s) << endl;
	//�������г���ͬ����Ա����Ҫ������������
	cout << "Baese1::m_A= " << s.Baese1::m_A << endl;
	cout << "Baese2::m_A= " << s.Baese2::m_A << endl;
}

int main()
{
	test01();
	

	system("pause");
	return 0;
}