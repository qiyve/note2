#include<iostream>
using namespace std;
#include<string>

//string ���Ӵ�

//string  substr ��int pos = 0��int  n = npos��const�� //������pos��ʼ��n���ַ���ɵ��ַ��� 

void test01()
{
	string str = "abcdefg";

	string substr = str.substr(0, 3);

	cout << "substr = " << substr << endl;
}

//ʹ�ò���
void test02()
{
	string email = "asan@sina.com";

	//���ʼ���ַ�� ��ȡ �û���Ϣ

	int pos = email.find("@");

	string usrName = email.substr(0, pos);

	cout << "�û�����" << usrName << endl;

}

int main()
{

	test01();

	test02();

	system("pause");
	return 0;
}