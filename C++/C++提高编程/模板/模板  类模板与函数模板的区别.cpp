#include<iostream>
using namespace std;
#include<string>

//�﷨��  template<typename T>  //   typenname ������class����


//��ģ��
template <class NameType,class AgeType=int>
class Person
{
public:

	Person(NameType name,AgeType age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

	void showPerson()
	{
		cout << "name��" << m_Name << " age��" << m_Age << endl;
	}


	NameType m_Name;
	AgeType m_Age;
};
//1.��ģ��û���Զ������Ƶ���ʹ�÷�ʽ
void test01()
{
	// Person p1("����", 15); �����޷����Զ������Ƶ�

	//����ָ��������ʾ
	Person<string, int>p1("����", 15);
	p1.showPerson();
}

//2.��ģ����ģ������б��п�����Ĭ�ϲ���
void test02()
{
	Person<string>p2("����", 15);
	p2.showPerson();
}

int main()
{
	test01();

	test02();
	
	system("pause");
	return 0;
}