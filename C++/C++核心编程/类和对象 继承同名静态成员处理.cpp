#include<iostream>
using namespace std;


//�̳���ͬ����Ա����

class Baese
{
public:

	static int m_A;
	static void func()
	{
		cout << "Baese -func����" << endl;
	}
	static void func(int a)
	{
		cout << "Baese -func int a����" << endl;
	}
};
int Baese::m_A = 100;

class Son:public Baese
{
public:
	
	static int m_A;
	static void func()
	{
		cout << "Son -func����" << endl;
	}
};

int Son::m_A = 200;

//ͬ����̬��Ա����
void test01()
{
	//ͨ���������
	cout << "ͨ���������" << endl;
	Son s;
	cout << "Son��m_A= " << s.m_A << endl;
	cout << "Baese��m_A= " << s.Baese::m_A << endl;

	//ͨ����������
	cout << "ͨ����������" << endl;
	cout << "Son��m_A= " << Son::m_A<< endl;
	//��һ��::����ͨ��������ʽ����  �ڶ���::������ʸ�����������	��
	cout << "Baese�� m_A= " << Son::Baese::m_A << endl;
}


//ͬ����̬��Ա����
void test02()
{
	//1��ͨ���������
	cout << "ͨ���������" << endl;
	Son s;
	s.func();
	s.Baese::func();

	//2/ͨ����������
	cout << "ͨ����������" << endl;
	Son::func();
	Son::Baese::func();

	//������ֺ͸���ͬ����̬��Ա������Ҳ�����ص�����������ͬ����Ա����
	//�������ʸ����б����ص�ͬ����Ա��������Ҫ��������
	Son::Baese::func(100);

}

int main()
{
	
	test01();

	test02();

	system("pause");
	return 0;
}