#include<iostream>
using namespace std;

//�������� ע������
//1��������Ϊ���ص�����
void func(int& a) // int &a =10 ���Ϸ�
{
	cout << "int &a �ĵ���" << endl;
}

void func(const int& a)  //const int &a =10 �Ϸ�
{
	cout << "const int &a �ĵ���" << endl;
}

//2��������������Ĭ�ϲ���
void func02(int a,int b=10) 
{
	cout << "int a int b �ĵ���" << endl;
}
void func02(int a) 
{
	cout << "int a �ĵ���" << endl;
}

int main()
{ 
	//1��������Ϊ���ص�����
	int a = 10;
	func(a);//������sonst  �ɶ���д

	
	func(10);//������ const  ֻ��
	
  //2��������������Ĭ�ϲ���
  
	//func02(10); //��������������Ĭ�ϲ��������ֶ����ԣ����壩���������������������


	system("pause");
	return 0;
}

