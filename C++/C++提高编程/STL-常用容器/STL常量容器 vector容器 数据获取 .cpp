#include<iostream>
using namespace std;
#include<vector>

// vector������ȡ
// at ( int idx );     // �������� idx��ָ������
// operator [ ];       // �������� idx��ָ������
// front();            // ���������е�һ������Ԫ��
// back����;           // �������������һ������Ԫ��


void test01()
{
	vector <int> v1;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
	}
	
	// ���� [] ��ʽ����������Ԫ��    size( )  Ԫ�ظ��� 
	for (int i = 0; i < v1.size(); i++)
	{
		cout << v1[i] << " ";
	}
	cout << endl;
	
	//����at���ʷ�ʽ����Ԫ��
	for (int i = 0; i < v1.size(); i++)
	{
		cout << v1.at(i) << " ";
	}
	cout << endl;

	//��ȡ��һ��Ԫ��
	cout << "��һ��Ԫ��Ϊ��" << v1.front() << endl;

	//��ȡ���һ��Ԫ��
	cout << "���һ��Ԫ��Ϊ��" << v1.back() << endl;
}



int main()
{

	test01();


	system("pause");
	return 0;
}