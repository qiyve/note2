#include<iostream>
using namespace std;
#include<string>

//pair����Ĵ���


//pair<type, tyep> p(value1, value2)��
//pair<type, type> p = make_pair(value1, value2);



void test01()
{
	//��һ�ַ�ʽ
	pair<string, int>p("Tom", 17);
	cout << "������" << p.first << " ����:" << p.second << endl;
	
	//�ڶ��ַ�ʽ
	pair<string, int>p2 = make_pair("Tom", 18);
	cout << "������" << p2.first << " ���䣺" << p2.second << endl;
}



int main()
{
	test01();
	
	

	system("pause");
	return 0;
}