#include<iostream>
using namespace std;
#include<set>

//set����  ��С�ͽ���


//size������     //����������Ԫ�ص���Ŀ
//empty������ //�ж������Ƿ�Ϊ��
//swap������   //����������������


void printSet(set<int>&s)
{
	for (set<int>::iterator it = s.begin(); it != s.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

//��С
void test01()
{
	set<int>s1;
	
	//��������  ֻ��insert��ʽ
	s1.insert(10);
	s1.insert(20);
	s1.insert(30);
	s1.insert(40);
	
	//��ӡ����
	printSet(s1);

	//�ж������Ƿ�Ϊ��
	if (s1.empty())
	{
		cout << "s1 Ϊ��" << endl;
	}
	else
	{
		cout << "s1 ��Ϊ��" << endl;
		cout << "Ԫ�صĸ���Ϊ��" << s1.size() << endl;
	}
}

//����
void test02()
{
	set<int>s1;
	//��������  ֻ��insert��ʽ
	s1.insert(10);
	s1.insert(20);
	s1.insert(30);
	s1.insert(40);

	set<int>s2;
	//��������  ֻ��insert��ʽ
	s2.insert(1);
	s2.insert(2);
	s2.insert(3);
	s2.insert(4);

	cout << "����ǰ" << endl;
	printSet(s1);
	printSet(s2);
	
	//����
	s2.swap(s1);
	cout << "������" << endl;
	printSet(s1);
	printSet(s2);
}
int main()
{
	//test01();
	
	test02();

	system("pause");
	return 0;
}