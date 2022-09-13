#include<iostream>
using namespace std;
#include<set>
#include<string>

//set���� ���� ����Զ�����������

class Person
{
public:

	Person(string name, int age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

	string m_Name;
	int m_Age;
};

class comparePerson
{
public:

	//��Ϊ�ȽϺ��������const �﷨�涨 �﷨�涨 �﷨�涨
	bool operator()(const  Person& p1, const  Person& p2)const
	{
		//�������С ����
		return p1.m_Age > p2.m_Age;
	}
};

void test01()
{
	//�Զ����������ͣ�����ָ���������
	set<Person, class comparePerson>s;

	//����Perosn����
	Person p1("����", 40);
	Person p2("����", 25);
	Person p3("����", 30);
	Person p4("����", 20);

	s.insert(p1);
	s.insert(p2);
	s.insert(p3);
	s.insert(p4);
	
	//��������
	for (set<Person, class comparePerson>::iterator it = s.begin(); it != s.end(); it++)
	{
		cout << "������" << it->m_Name << " ���䣺" << it->m_Age << endl;
	}

}
int main()
{
	test01();
	

	system("pause");
	return 0;
}