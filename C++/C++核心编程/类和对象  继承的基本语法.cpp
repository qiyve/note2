#include<iostream>
using namespace std;
#include<string>

//�̳�

//��ͨʵ��ҳ��
//javaҳ��
//class Java
//{
//public:
//
//	void header()
//	{
//		cout << "��ҳ�������Ρ���¼��ע��...(����ͷ��)" << endl;
//	}
//
//	void footer()
//	{
//		cout << "�������ġ�����������վ�ڵ�ͼ...(�����ײ�)" << endl;
//	}
//
//	void left()
//	{
//		cout << "Java��Python��C++...(���������б�)" << endl;
//    }
//
//	void content()
//	{
//		cout << "Javaѧ����Ƶ" << endl;
//	}
//};


//�̳�ʵ��ҳ��

//����ҳ����
class BasePage
{
public:

	void header()
	{
		cout << "��ҳ�������Ρ���¼��ע��...(����ͷ��)" << endl;
	}

	void footer()
	{
		cout << "�������ġ�����������վ�ڵ�ͼ...(�����ײ�)" << endl;
	}

	void left()
	{
		cout << "Java��Python��C++...(���������б�)" << endl;
	}
};

//Javaҳ��
class Java :public BasePage
{
public:

	void content()
	{
		cout << "Javaѧ����Ƶ" << endl;
	}
};

//Pythonҳ��
class Python: public BasePage
{
public:

	void content()
	{
		cout << "Pythonѧ����Ƶ" << endl;
	}
};

//C++ҳ��
class CPP : public BasePage
{
public:

	void content()
	{
		cout << "CPPѧ����Ƶ" << endl;
	}
};
void tets01()
{

	cout << "Java������Ƶҳ�����£�" << endl;
	Java ja;
	ja.header();
	ja.footer(); 
	ja.left();
	ja.content();

	cout << "����������������������������" << endl;
	cout << "Python������Ƶҳ�����£�" << endl;
	Python py;
	py.header();
	py.footer();
	py.left();
	py.content();

	cout << "����������������������������" << endl;
	cout << "C++������Ƶҳ�����£�" << endl;
	CPP cpp;
	cpp.header();
	cpp.left();
	cpp.content();
}
int main()
{
	
	tets01();

	system("pause");
	return 0;
}