#include<iostream>
using namespace std;
#include<deque>
#include<algorithm>//��׼�㷨ͷ�ļ�

//deque��������
//sort(iterator beg, iterator end);    // ��beg ��end ������Ԫ�ؽ�������

void printDeque(const deque<int>&d)//ֻ��
{
	for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void test01()
{
	deque<int>d;
	d.push_back(1);
	d.push_back(2);
	d.push_back(3);
	d.push_front(4);
	d.push_front(5);
	d.push_front(6);

	//6 5 4 1 2 3 
	printDeque(d);

	//����
	sort(d.begin(), d.end());
	cout << "�����" << endl;
	printDeque(d);
	
}


int main()
{

	test01();
	

	system("pause");
	return 0;
}