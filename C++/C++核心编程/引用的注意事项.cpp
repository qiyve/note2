#include<iostream>
using namespace std;



int main()
{
	//���õ�ע������
	//1. ���ñ����ʼ��
	
	int a = 10;
	//int& b;  // ���� �����ʼ��
	
	//2. �����ڳ�ʼ���󣬲����Ըı�

	int& b = a;// һ����ʼ���þͲ����Ը���
	int c = 100;

	b = c;//���Ǹ�ֵ���������Ǹ������� 

	
	
	cout << "a= " << a << endl;
	cout << "b= " << b << endl;
	cout << "c= " << c << endl;
	
		

	
	system("pause");
	return 0;
}