#include<iostream>
using namespace std;


//��Ա���� ��  ��Ա���� �ֿ��洢��

class Person
{

	int m_A;//�Ǿ�̬��Ա����  ������Ķ�����

	static int m_B;//��̬��Ա���� �������������

	void func(){}//�Ǿ�̬����

};

int Person::m_B = 0;  //��̬��Ա���� �ص㣺�������� �����ʼ��

void test01()
{
	Person p;
	//�ն���ռ���ڴ�ռ�Ϊ ��1
	//C++���������ÿһ���ն���Ҳ����һ���ֽڿռ䣬��Ϊ�����ֿն���ռ�ڴ��λ��
	//ÿ���ն���ҲӦ����һ����һ�޶����ڴ��ַ
	cout << "sizeof p =" << sizeof(p) << endl;
}


void test02()
{
	Person p2;
	cout << "sizeof p2 =" << sizeof(p2) << endl;
}
int main()
{
	//test01();

	test02();

	system("pause");
	return 0;
}