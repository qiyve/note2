#include<iostream>
using namespace std;
#include<string>

//�ַ����Ĳ��Һ��滻

//1������
void test01()
{

	string str1 = "abcdefgde";

	//int find(const string & str, int pos = 0) const; //����str��һ�γ���λ��,��pos��ʼ����

	int pos =str1.find("de"); //��0���±�����

	if (pos == -1)
	{
		cout << "δ�ҵ��ַ���" << endl;
	}
	else
	{
		cout << "�ҵ��ַ�����pos = " << pos << endl;
	}

	//rfind ��find����
	//rfind �Ǵ�������飬  find �Ǵ������Ҳ�
	 pos =str1.rfind("de");
	cout << "pos = " << pos << endl;
}

//2���滻
void test02()
{
	string str2 = "abcdefg";
	str2.replace(1, 3, "1111");

	cout << "str2 = " << str2 << endl;
}

int main()
{

	test01();

	test02();
	

	system("pause");
	return 0;
}