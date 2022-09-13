#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include<string>

//���ò����㷨  find_if

//find(iterator beg, iterator end, _pred);
//��ֵ����Ԫ�أ��ҵ�����ָ��λ�õ��������Ҳ������ؽ���������
//beg ��ʼ������
//end ����������
//_pred ��������ν�� ������bool���͵ķº�����
//����find��������������ָ����Ԫ�أ�����ֵ�ǵ�����

//1������������������
class GreaterFive
{
public:

	bool operator()(int val)
	{
		return val > 5;
	}
};
void test01()
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}

	//���Ҵ���5 ��Ԫ��
	vector<int>::iterator it = find_if(v.begin(), v.end(), GreaterFive());
	if (it == v.end())
	{
		cout << "δ�ҵ�" << endl;
	}
	else
	{
		cout << "�ҵ�����5��Ԫ�أ�" << *it << endl;
	}
}

//2�������Զ�����������
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

//ν��
class Greater20
{
public:
	bool operator()(const Person& p)
	{
		return  p.m_Age > 50;
	}
};


void test02()
{
	vector<Person>v;

	//��������
	Person p1("aaa", 10);
	Person p2("bbb", 20);
	Person p3("ccc", 30);
	Person p4("ddd", 40);

	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);
	v.push_back(p4);

	//���������20����
	vector<Person>::iterator it = find_if(v.begin(), v.end(), Greater20());

	if (it == v.end())
	{
		cout << "δ�ҵ�" << endl;
	}
	else
	{
		cout << "�ҵ��� ������" << it->m_Name << " ���䣺" << (*it).m_Age << endl;
	}
}
int main()
{
	//test01();
	test02();

	system("pause");
	return 0;
}