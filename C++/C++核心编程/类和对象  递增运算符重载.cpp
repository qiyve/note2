#include<iostream>
using namespace std;

//���ص��������

//�Զ�������
class MyInteger
{    
	//������Ԫ�ؼ��� �������˽������
	friend ostream& operator<<(ostream& cout, MyInteger myint);

public:
	MyInteger()
	{
		m_Num = 0;
	}

	//����ǰ��++�����  ��������Ϊ��һֱ��һ�����ݽ��е�������
	MyInteger& operator++()
	{
		m_Num++;
		return *this;//this��ָ��������*������ ����
	 }


	//���غ���++�����
	//MyInteger operator++(int) ���int����ռλ����������������ǰ�úͺ��õ���
	MyInteger operator++(int)
	{
		//�ȼ�¼��ʱ���
		MyInteger temp;
		//�� ����
		m_Num++;
		//��󽫼�¼�Ľ��������
		return temp;
	}
private:

	int m_Num;
};


//����<<�����
ostream &operator<<(ostream &cout, MyInteger myint)
{
	cout << myint.m_Num;
	return cout;
}

//ǰ�õ���
void test01()
{
	MyInteger myint;

	cout << ++(++myint) << endl;//2

	cout << myint << endl;//2
}

//���õ���
void test02()
{
	MyInteger myint;

	cout << myint++<< endl;//0

	cout << myint << endl;//1
}
int main()
{
	test01();


	test02();

	//int a = 0;
	//cout << ++(++a) << endl;
	//cout << a << endl;


	system("pause");
	return 0;
}