#include<iostream>
using namespace std;

//���صݼ������

//����һ���Զ�������
class MyInteger
{

	//������Ԫ����˽������ �ؼ��� friend
	friend ostream& operator<<(ostream& cout, MyInteger mayint); 

public:
	MyInteger()
	{
		m_Num = 2;
	}

	//ǰ�õݼ� --�����
	MyInteger& operator--()
	{
		m_Num--;
		return *this;
	}
	//���õݼ�--�����
	MyInteger operator--(int)//int ռλ���� ����ǰ��ݼ�
	{
		//�ȼ�¼��ǰ���
		MyInteger temp;
		//�� �ݼ�
		m_Num--;
		//���ؼ�¼���
		return temp;
	}
private:

	int m_Num;
};

//����<<�����
ostream& operator<<(ostream& cout, MyInteger mayint)
{
	cout << mayint.m_Num;
	return cout;
}

//ǰ�õݼ�
void test01()
{
	MyInteger myint;

	cout <<-- myint << endl;
	cout << myint << endl;
}

//���õݼ�  �ȷ��ؽ�� Ȼ������ - 1 ����
void test02()
{
	MyInteger myint;

	cout << myint-- << endl;
	cout << myint << endl;

}

int main()
{
	//test01();

	test02();


	system("pause");
	return 0;
}