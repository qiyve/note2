#include<iostream>
using namespace std;
#include<map>

//map���� ��С�ͽ���

//size������          //����������Ԫ�ص���Ŀ
//empty();           //�ж������Ƿ�Ϊ��
//swap ����;          //����������������

void printMap(map<int, int>& m)
{
	for (map<int, int>::iterator it = m.begin(); it != m.end(); it++)
	{
		cout << "key = " << it->first << " value = " << it->second << endl;
    }
	cout << endl;
}

//��С
void test01()
{
	map<int, int>m1;

	m1.insert(pair<int, int>(1, 10));
	m1.insert(pair<int, int>(2, 20));
	m1.insert(pair<int, int>(3, 30));
	m1.insert(pair<int, int>(4, 40));

	if (m1.empty())  //Ϊ�� ����Ϊ��
	{
		cout << "m1 Ϊ��" << endl;
	}
	else
	{
		cout << "m1 ��Ϊ��" << endl;
		// Ԫ�ظ���Ϊ
		cout << "m�Ĵ�СΪ��" << m1.size() << endl;
	}

	
}

//����
void test02()
{
	map<int, int>m1;

	m1.insert(pair<int, int>(1, 10));
	m1.insert(pair<int, int>(2, 20));
	m1.insert(pair<int, int>(3, 30));
	
	map<int, int>m2;
	m2.insert(pair<int, int>(4, 100));
	m2.insert(pair<int, int>(5, 200));
	m2.insert(pair<int, int>(6, 300));

	cout << "����ǰ " << endl;
	printMap(m1);
	printMap(m2);

	//��ʼ����
	m2.swap(m1);

	cout << "---------------------" << endl;
	cout << "������ " << endl;
	printMap(m1);
	printMap(m2);
}
int main()
{
	test01();
	
	test02();

	system("pause");
	return 0;
}