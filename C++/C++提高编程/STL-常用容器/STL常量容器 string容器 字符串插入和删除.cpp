#include<iostream>
using namespace std;
#include<string>

//�ַ��� �����ɾ��

//string& insert(int pos, const char* s);      //�����ַ��� 
//string& insert(int pos, const  string& str); //�����ַ���
//string& insert(int pos, int  n, char  c);    //��ָ��λ�ò���n���ַ�c
//string& erase(int pos, int  n = npos);       //ɾ����pos��ʼ��n���ַ�

//�����ɾ������ʼ�±궼�Ǵ�0��ʼ

void test01()
{
	string str = "hello";

	//����
	str.insert(1, "111");
	//h111ello
	cout << "str = " << str << endl;

	//ɾ��
	str.erase(1, 3);
	//hello
	cout << "str = " << str << endl;
}

int main()
{

	test01();


	system("pause");
	return 0;
}