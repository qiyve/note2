#include<iostream>
using namespace std;
#include<string>

//�̳��й��������˳��

//�����̳�
class Baese
{
public:
	
	Baese()
	{
		cout << "Baese�Ĺ��캯��" << endl;
	}
	~Baese()
	{
		cout << "Baese����������" << endl;
	}
};

class Son:public Baese
{
public:
	Son()
	{
		cout << "Son�Ĺ��캯��" << endl;
	}
	~Son()
	{
		cout << "Son����������" << endl;
	}
	
};


void test01()
{
	Baese b;

	//Son s;
}
int main()
{
	
	test01();

	system("pause");
	return 0;
}