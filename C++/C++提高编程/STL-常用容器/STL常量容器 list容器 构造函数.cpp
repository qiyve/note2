#include<iostream>
using namespace std;
#include<list>

//list���� ���캯��

//list<T>;            //list���ò���ģ����ʵ�֣������Ĭ�Ϲ�����ʽ
//list(beg, end); //���캯������beg, end �������е�Ԫ�ؿ���������
//list(n, elem);     //���캯����n��elem����������
//list(const list& lst); //�������캯��

void printList(const list<int>&L)
{    //�޶�ֻ��
	for (list<int>::const_iterator it = L.begin(); it != L.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void test01()
{
	list<int>L1; //Ĭ�Ϲ���

	//�������
	L1.push_back(10);
	L1.push_back(20);
	L1.push_back(30);
	L1.push_back(40);

	printList(L1);

	//���䷽ʽ
	list<int>L2(L1.begin(), L1.end());
	printList(L1);

	//n��elem
	list<int>L3(5, 10);
	printList(L3);

	//��������
	list<int>L4(L3);
	printList(L4);
}



int main()
{
	test01();
	

	system("pause");
	return 0;
}