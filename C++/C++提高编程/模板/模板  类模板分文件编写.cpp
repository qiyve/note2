#include<iostream>
using namespace std;
#include<string>

//Դ��

//��ģ����ļ���д�����Լ����
//�ܽ᣺�����Ľ�������ǵڶ��֣�����ģ���Ա����д��һ�𣬲�����׺����Ϊ .cpp 

//��һ�ֽ����ʽ��ֱ�Ӱ��� Դ�ļ�
// #include"Person.cpp"

//�ڶ��ֽ����ʽ���� .h �� .cpp����д��һ�𣬽���׺��Ϊ .hpp   .hpp��Լ��������
#include"Person.hpp"

//template<class T1,class T2>
//class Person
//{
//public:
//
//	Person(T1 name, T2 age);
//
//	void showPerson();
//
//	T1 m_Name;
//	T2 m_Age;
//};

////����ʵ�ֹ��캯��
//template<class T1,class T2>
//Person<T1, T2>::Person(T1 name, T2 age)
//{
//	m_Name = name;
//	m_Age = age;
//}
//
////����ʵ�ֳ�Ա����
//template<class T1, class T2>
//void Person<T1, T2>::showPerson()
//{
//	cout << "������" << this->m_Name << " ���䣺" << m_Age << endl;
//}

void test01()
{
	Person<string, int>p("Tom", 18);
	p.showPerson();
}

int main()
{
	test01();

	system("pause");
	return 0;
}