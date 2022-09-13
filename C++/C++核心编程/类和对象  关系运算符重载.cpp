#include<iostream>
using namespace std;
#include<string>

//��ϵ���������
class Person
{
public:

	Person(string name,int age)
	{
		m_Name = name;
		m_Age = age;
	}
	//���� == ��
	bool operator==(Person &p)
	{
		//�ж��Ƿ���� ��ȷ���һ���� true  ����ȷ��ؼ� false
		if (this->m_Name == p.m_Name && this->m_Age == p.m_Age)
		{
			return true;
		}
		return false;
	}

	//���� ��= ��
	bool operator!=(Person & p)
	{
		//�ж��Ƿ���� ����ȷ����� true  ��ȷ��ؼ� false
		if (this->m_Name != p.m_Name && this->m_Age != p.m_Age)
		{
			return true;
		}
		return false;
	}

public:

	string m_Name;

	int m_Age;
};

void test01()
{
	Person p1("Tom", 10);

	Person p2("Tom", 10);

	if (p1 == p2)
	{
		cout << "p1��p2����ȵģ�" << endl;
	}
	else
	{
		cout << "p1��p2�ǲ���ȵģ�" << endl;
	}

	if (p1 != p2)
	{
		cout << "p1��p2�����" << endl;
	}
	else
	{
		cout << "p1��p2���" << endl;
	}
}



int main()
{
	test01();

	

	system("pause");
	return 0;
}