#include<iostream>
using namespace std;
#include<string>


//�������Ϊ���Ա


//�ֻ���
class Phone
{
public:

	Phone(string pName)
	{
		m_PName = pName;

		cout << "Phone�Ĺ��캯������" << endl;
	}
	~Phone()
	{
		cout << "Phone��������������" << endl;
	}

	//�ֻ�Ʒ��
	string m_PName;
	
};

//����
class Person
{
public:

	//phone m_phone = pName   ��ʽת����
	Person(string name, string pName):m_Name(name),m_phone(pName)
	{
		cout << "Person�Ĺ��캯������" << endl;
	}

	~Person()
	{
		cout << "Person��������������" << endl;
	}

	//����
	string m_Name;

	//�ֻ�
	Phone m_phone;

};

//�������������Ϊ�����Ա������ʱ���ȹ���������ڹ�������

void test01()
{
	Person p("����","ƻ��MAX");

	cout << p.m_Name << "���ţ�" << p.m_phone.m_PName << endl;
}
int main()
{
	test01();

	system("pause");
	return 0;
}