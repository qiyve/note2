#include<iostream>
using namespace std;
#include<deque>

//deque�������ݴ�ȡ

//at ( int idx );    // �������� idx��ָ������
//operator [ ];      // �������� idx��ָ������
//front������        // ���������е�һ������Ԫ��
//back������         // �������������һ������Ԫ��  

void test01()
{
	deque<int>d1;
	d1.push_back(10);
	d1.push_back(20);
	d1.push_back(30);
	d1.push_front(100);
	d1.push_front(200);
	d1.push_front(300);

	//ͨ��[] ��ʽ����Ԫ��
	//300 200 100 10 20 30
	for (int i=0;i<d1.size();i++)
	{
		cout << d1[i]<< " ";
	}
	cout << endl;

	//ͨ��at��ʽ
	//300 200 100 10 20 30
	for (int i = 0; i < d1.size(); i++)
	{
		cout << d1.at(i) << " ";
	}
	cout << endl;

	//���ʵ�һ��Ԫ�� front()
	cout << "��һ��Ԫ�أ�" << d1.front() << endl;

	//�������һ��Ԫ�� back������  
	cout << "���һ��Ԫ�أ�" << d1.back() << endl;
}


int main()
{

	test01();
	

	system("pause");
	return 0;
}