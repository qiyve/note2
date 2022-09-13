#include<iostream>
using namespace std;
#include"MyArray.hpp"


void printIntArray(MyArray<int> &arr)
{
	for (int i = 0; i < arr.getSize(); i++)
	{
		cout << arr[i] << endl;
	}
}


void test01()
{
	MyArray<int> arr1(5);

	for (int i = 0; i < 5; i++)
	{
		//����β�巨�������в�������
		arr1.Push_Back(i);
	}
	cout << "arr1�Ĵ�ӡ���Ϊ��" << endl;

	printIntArray(arr1);

	cout << "arr1 ������Ϊ��" << arr1.getCapacity() << endl;
	cout << "arr1 �Ĵ�СΪ��" << arr1.getSize() << endl;

	MyArray<int>arr2(arr1);

	cout << "arr2 �Ĵ�ӡ���" << endl;

	printIntArray(arr2);

	//βɾ
	arr2.Pop_Back();

	cout << "arr2 βɾ��" << endl;
	cout << "arr2 ������Ϊ��" << arr2.getCapacity() << endl;
	cout << "arr2 �Ĵ�СΪ��" << arr2.getSize() << endl;

	//MyArray<int>arr2(arr1);

	//MyArray<int>arr3(100);
	//arr3 = arr1;
}

//�����Զ�����������
class Person
{
public:

	Person() {};//Ĭ�Ϲ���

	//�вι���
	Person(string name, int age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

	string m_Name;
	int m_Age;
};

void printPerson(MyArray<Person>&arr)
{
	for (int i = 0; i < arr.getSize(); i++)
	{
		cout << "������" << arr[i].m_Name << " ���䣺" << arr[i].m_Age << endl;
	}
}
void test02()
{
	MyArray<Person>arr(10);

	Person p1("����", 15);
	Person p2("����", 45);
	Person p3("����", 42);
	Person p4("����", 40);

	//�����ݲ��뵽������
	arr.Push_Back(p1);
	arr.Push_Back(p2);
	arr.Push_Back(p3);
	arr.Push_Back(p4);

	//��ӡ���
	printPerson(arr);

	//�������
	cout << "Person ��������" << arr.getCapacity() << endl;
	//�����С
	cout << "Person�Ĵ�С" << arr.getSize() << endl;
}


int main()
{

	//test01();

	test02();

	system("pause");
	return 0;
}