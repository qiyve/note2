#include<iostream>
using namespace std;
#include<string>

//ͨ��ȫ�ֺ�������ӡPerson ��Ϣ

template<class T1,class T2>
class Person;

//����ʵ��
template<class T1, class T2>
void printPerson2(Person<T1, T2>& p)
{
	cout << "����ʵ��---������" << p.m_Name << " ���䣺" << p.m_Age << endl;
}

template<class T1,class T2>
class Person
{
	//ȫ�ֺ���  ����ʵ��
	friend void printPerson(Person<T1,T2>&p)
	{
		cout << "������" << p.m_Name << " ���䣺" << p.m_Age << endl;
	}

	//ȫ�ֺ��� ����ʵ��
	//�ӿ�ģ������б�
	friend void printPerson2<>(Person<T1, T2>& p);

public:

	Person(T1 name,T2 age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

private:

	T1 m_Name;
	T2 m_Age;
};



//ȫ�ֺ���������ʵ��
void test01()
{
	Person<string, int>p("Tom", 17);
	
	printPerson(p);
}

//ȫ�ֺ���������ʵ��
void test02()
{
	Person<string, int>p("����", 17);

	printPerson2(p);
}

int main()
{
	//test01();

	test02();

	system("pause");
	return 0;
}