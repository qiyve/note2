#include<iostream>
using namespace std;

//��������
// ������������ͬ����߸�����
//�����ú�������ͬ����ߺ����ĸ�����

// (1)ͬһ����������                         
//( 2)  ��������ͬ
//��3�� �����������Ͳ�ͬ���߸�����ͬ ���� ˳��ͬ

//������ͬ
void func()
{
	cout << "func�ĵ���" << endl;
}
void func(int a)
{
	cout << "func(int a)" << endl;
}

//���Ͳ�ͬ
void func(int a)
{
	cout << "func(int a)" << endl;
}
void func(double a)
{
	cout << "func(double a)" << endl;
}



//˳��ͬ
void func(double a,int b)
{
	cout << "func(double a,int b)" << endl;
}
void func( int b,double a )
{
	cout << "func(int b,double a)" << endl;
}
//ע������
//�����ķ���ֵ��������Ϊ�������ص�����
//int func(int b, double a)
//{
//	cout << "func(int b,double a)" << endl;
//}

int main()
{
	//������ͬ
	func();
	func(10);

	//���Ͳ�ͬ
	func(10);
	func(3.14);

	//˳��ͬ
	func(3.14, 10);
	func(10, 3.14);


	

	system("pause");
	return 0;
}

