#include<iostream>
using namespace std;
#include<list>

//list���� ���ݴ�ȡ

//front();     //���ص�һ��Ԫ��
//back();     //�������һ��Ԫ��

void test01()
{
	list<int>L1; 

	//β��
	L1.push_back(10);
	L1.push_back(20);
	L1.push_back(30);
	L1.push_back(40);

	//L1[0]; ��������[]����list�����е�Ԫ��

	//L1.at(); ��������at��ʽ����list�����е�Ԫ��

	//ԭ����list���������������������Կռ�洢���ݣ�������Ҳ�ǲ�֧��������ʵ�

	cout << "��һ��Ԫ��Ϊ��" << L1.front() << endl;
	cout << "���һ��Ԫ��Ϊ��" << L1.back() << endl;

	//
}



int main()
{
	test01();
	


	system("pause");
	return 0;
}