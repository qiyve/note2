#include<iostream>
using namespace std;
#include<string>
#include<list>


//list���� ������ �����Զ����������� ������

//���������� ��Person�Զ����������ͽ�������Person�����������������䡢���
//������� ������������������������ͬ������߽��н���


class Person
{
public:
	Person(string name, int age, int hg)
	{
		this->m_Name = name;
		this->m_Age = age;
		this->m_Height = hg;
	}


	string m_Name; //����
	int  m_Age;  // ����
	int m_Height;//���
};

//ָ���������
bool comparPerson(Person& p1, Person p2)
{
	//������ ����  ���������ͬ ����߽���
	if (p1.m_Age == p2.m_Age)
	{
		//����� ����
		return p1.m_Height > p2.m_Height;
	}
	else
	{
		return p1.m_Age < p2.m_Age;
	}
}

void test01()
{
	list<Person>L;

	//׼������
	Person p1("����", 25, 170);
	Person p2("����", 30, 175);
	Person p3("�ܲ�", 40, 160);
	Person p4("�ŷ�", 30, 180);
	Person p5("����", 30, 190);
	Person p6("��Ȩ", 35, 195);

	//��������
	L.push_back(p1);
	L.push_back(p2);
	L.push_back(p3);
	L.push_back(p4);
	L.push_back(p5);
	L.push_back(p6);

	for (list<Person>::iterator it = L.begin(); it != L.end(); it++)
	{
		cout << "������" << (*it).m_Name 
			<< " ���䣺" << (*it).m_Age  // Ҳ����ָ���ȡ����
			<< " ��ߣ�" << it->m_Height << endl;
	}

	//����
	cout << "------------------------------" << endl;
	cout << "�����" << endl;

	L.sort(comparPerson);

	for (list<Person>::iterator it = L.begin(); it != L.end(); it++)
	{
		cout << "������" << (*it).m_Name
			<< " ���䣺" << (*it).m_Age  
			<< " ��ߣ�" << it->m_Height << endl;
	}
}

int main()
{
	test01();
	
	

	system("pause");
	return 0;
}