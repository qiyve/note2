#include<iostream>
using namespace std;
#include<fstream> //����ͷ�ļ�


//�������ļ� д�ļ�

class Person
{
public:

	char m_Name[64];//����
	int m_Age;//����
};
void test01()
{
	//1������ͷ�ļ�

	//2������������
	ofstream ofs("person.txt", ios::out | ios::binary);

	//3�����ļ� 
	//ofs.open("person.txt", ios::out | ios::binary);

	//4��д����  ����ԭ�� ��ofstream& write (const char * buffer, int len);
	Person p = { "����",17 };
	ofs.write((const char*)&p, sizeof(Person));

	//5���ر��ļ�
	ofs.close();
}

int main()
{

	test01();

	system("pause");
	return 0;
}