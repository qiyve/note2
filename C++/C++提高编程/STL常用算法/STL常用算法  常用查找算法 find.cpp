#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include<string>


//���ò����㷨  find

//find(iterator beg, iterator end, value);
//��ֵ����Ԫ�أ��ҵ�����ָ��λ�õĵ��������Ҳ������ؽ���������λ��
//beg ��ʼ������
//end ����������
//value ���ҵ�Ԫ��

//���� ������������
void test01()
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}

	//���� ������ �Ƿ��� 5���Ԫ�ش���
	vector<int>::iterator it = find(v.begin(), v.end(), 5);
	if (it == v.end())
	{
		cout << "û���ҵ�" << endl;
	}
	else
	{
		cout << "�ҵ���Ԫ�� ��" << *it << endl;
	}
	
}

class Person
{
public:
	Person(string name, int age)
	{
		this->m_Nmae = name;
		this->m_Age = age;
	}

	//���� == �ײ�find֪����ζԱ�Person��������
	bool operator==(const Person &p)
	{
		if (this->m_Nmae == p.m_Nmae && this->m_Age == p.m_Age)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	string m_Nmae;
	int m_Age;

};
//���� �Զ�����������
void test02()
{
	vector<Person>v;
    
	Person p1("����", 15);
	Person p2("����", 35);
	Person p3("����", 65);
	Person p4("����", 25);

	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);
	v.push_back(p4);

	Person pp("����", 15);

	vector<Person>::iterator it = find(v.begin(), v.end(), pp);
	if (it == v.end())
	{
		cout << "δ�ҵ�" << endl;
	}
	else
	{
		cout << "�ҵ��� --- ������" << it->m_Nmae << " ���䣺" << it->m_Age << endl;
	}


}

int main()
{
	//test01();
	test02();

	system("pause");
	return 0;
}