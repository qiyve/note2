#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include<string>


//���ò����㷨  count


//count(iterator beg, iterator end, value);
//ͳ��Ԫ�س��ִ���
//beg ��ʼ������
//end ����������
//value ͳ�Ƶ�Ԫ��

//1��ͳ��������������
void test01()
{
	vector<int>v;
	v.push_back(10);
	v.push_back(30);
	v.push_back(20);
	v.push_back(30);
	v.push_back(20);
	v.push_back(20);

	int num = count(v.begin(), v.end(), 20);
	
	cout << "20��Ԫ�ظ�����" << num << endl;
}

//2��ͳ���Զ�����������
class Person
{
public:
	Person(string name, int age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

	bool operator==(const Person& p)
	{
		if (this->m_Age == p.m_Age)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	string m_Name;
	int m_Age;
};

void test02()
{
	vector<Person>v;

	Person p1("aa", 10);
	Person p2("bb", 20);
	Person p3("cc", 40);
	Person p4("dd", 30);
	Person p5("ee", 10);

	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);
	v.push_back(p4);
	v.push_back(p5);

	//ͳ�ƺ�ss ͬ��������
	Person p("ss", 10);
	
	int num = count(v.begin(), v.end(),p);

	cout << "��ssͬ��������Ա������" << num << endl;



}
int main()
{
	//test01();
	
	test02();

	system("pause");
	return 0;
}