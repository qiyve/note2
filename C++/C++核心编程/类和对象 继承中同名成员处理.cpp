#include<iostream>
using namespace std;


//�̳���ͬ����Ա����

class Baese
{
public:

	Baese()
	{
		m_A = 10;
	}

	void func()
	{
		cout << "Baese ��������" << endl;
	}
	void func(int)
	{
		cout << "Baese int ��������" << endl;
	}

	int m_A;
};

class Son:public Baese
{
public:
	Son()
	{
		m_A = 100;
	}

	void func()
	{
		cout << "Son ��������" << endl;
	}
	int m_A;
};

//ͬ����Ա����
void test01()
{
	Son s;

	cout << "Son �� m_A= " << s.m_A << endl;
	//���ͨ��������� ���ʵ�������ͬ����Ա����Ҫ��������
	cout << "Baese �� m_A= " << s.Baese::m_A << endl;
}

//ͬ����Ա����
void test02()
{
	Son s;
	s.func();//ֱ�ӵ��ã������������е�ͬ����Ա

	//��ε��õ�������ͬ����Ա������
	s.Baese::func();

	//��������г��ֺ͸�����ͬ����Ա�����������ͬ����Ա�����ص�����������ͬ����Ա����
	//�������ʸ����б����ص�ͬ����Ա��������Ҫ��������
	s.Baese::func(100);
}

int main()
{
	
	//test01();

	test02();

	system("pause");
	return 0;
}