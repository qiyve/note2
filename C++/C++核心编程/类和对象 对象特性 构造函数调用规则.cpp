#include<iostream>
using namespace std;


// ���캯�����ù���
//1��Ĭ������£�C++���������ٸ�һ���� ���3������
// Ĭ�Ϲ��죨��ʵ�֣�
// ������������ʵ�֣�
// �������죨ֵ������

//2���������д���вι��캯���������Ͳ����ṩĬ���޲ι��죬��Ȼ�ṩĬ�Ͽ�������
//   ����û����忽�����캯����c++�������ṩ����������

class Person
{
public:
	//Person() //Ĭ�Ϲ���
	//{
	//	cout << "PersonĬ�Ϻ�������" << endl;
	//}

	//Person(int a)//�вι���
	//{
	//	cout << "Person�вι��캯���ĵ���" << endl;
	//	m_Age = a;
	//}

	Person(const Person& p)//��������
	{
		cout << "Person�������캯���ĵ���" << endl;
		m_Age = p.m_Age;
	}

	~Person()
	{
		cout << "Person�����������ĵ���" << endl;
	}
	int m_Age;
};


//void test01()
//{
//	Person p;
//	p.m_Age = 18;
//
//	Person p2(p);
//
//	cout << "p2������Ϊ��"<<p2.m_Age << endl;
//}


void test02()
{
	Person p;
	
}
int main()
{
	//test01();
	
	test02();

	system("pause");
	return 0;
}