#include<iostream>
using namespace std;
#include<string>

//string ���캯��ԭ��
//string����;                      // ����һ���յ��ַ��������� string_str;
//string(const char* s);    //���ַ���s��ʼ��
//string(const string& str);  // ʹ��һ��string�����ʼ����һ��string����
//string(int n, char c);        //ʹ��n���ַ�c��ʼ��

void test01()
{
	string s1; //Ĭ�Ϲ���

	const char* str = "hello world"; //���ַ���s��ʼ��
	string s2(str);

	cout << "s2 = " << s2 << endl;

	string s3(s2); //��������
	cout << "s3 = " << s3 << endl;

	string s4(5, 'b');
	cout << "s4 = " << s4<< endl;

}
int main()
{

	test01();

	

	system("pause");
	return 0;
}