#include<iostream>
using namespace std;
#include<string>

//string�ַ���ƴ��

//1��string & operator+=(const char* str);     //����+=������
//2��string & operator+=(const char c)��       //����+=������
//3��string & operator+=(const string & str);  //����+=������
//4��string & append(const char* s);           //���ַ���s���ӵ���ǰ�ַ�����β
//5. string& append(const char *s,int n);      //���ַ���s��ǰn���ַ����ӵ���ǰ�ַ�����β
//6��string & append(const char* s, int n);    //ͬoperator+=(const string& str)
//7��string & append(const string & s, int pos, int n); //�ַ���s�д�pos��ʼ��n���ַ����ӵ��ַ�����β


void test01()
{
	string str1 = "��";

	str1 += "����";
	cout << "str1 = " << str1 << endl;

	str1 += ':';
	cout << "str1 = " << str1 << endl;

	string str2 = "LOL CF";

	str1 += str2;
	cout << "str1 = " << str1 << endl;


	string str3 = "I";

	str3.append("love");
    
	cout << "str3 = " << str3 << endl;


	str3.append("game abcde", 4);
	
	cout << "str3 = " << str3 << endl;

	//str3.append(str2,0,3);//ֻ��ȡ LOL
	str3.append(str2, 4, 2);//ֻ��ȡ CF

	cout << "str3 = " << str3 << endl;



}
int main()
{

	test01();

	

	system("pause");
	return 0;
}