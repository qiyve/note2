#include<iostream>
using namespace std;


//��̬��Ա����
//���ж�����ͬһ������
//��̬��Ա����ֻ���ʾ�̬��Ա����



class  Person
{
public:

	//��̬��Ա����  ��ǰ����� static
	static void func()
	{
		cout << "static void func����" << endl;
	}

};

void test01()
{
	//1.ͨ���������
	Person p;
	p.func();

    //2.ͨ����������
	Person::func;
}
int main()
{
	test01();

	system("pause");
	return 0;
}