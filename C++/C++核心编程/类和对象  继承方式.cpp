#include<iostream>
using namespace std;
#include<string>

//�̳з�ʽ

//�����̳�
class Baese1
{
public:
	int m_A;
protected:
	int m_B;
private:
	int m_C;
};

class Son1 :public Baese1
{
public:

	void func()
	{
		m_A = 10;// �����еĹ���Ȩ�޳�Ա  ����������Ȼ�ǹ���Ȩ�� 
		m_B = 10;// �����еı���Ȩ�޳�Ա  ����������Ȼ�Ǳ���Ȩ��
		//m_C = 10;// �����е�˽��Ȩ���Ա  ������ʲ���
	}
};

void test01()
{
	Son1 s1;
	s1.m_A = 100;
	//s1.m_B = 100;//��Son1�� m_B �Ǳ���Ȩ�� ������ʲ���
}

//�����̳�
class Baese2
{
public:
	int m_A;
protected:
	int m_B;
private:
	int m_C;
};

class Son2 :protected Baese2
{
protected:
	void func()
	{
		m_A = 10;// �����еĹ���Ȩ�޳�Ա �������б�Ϊ����Ȩ��
		m_B = 10;// �����еı���Ȩ�޳�Ա ����������Ȼ�Ǳ���Ȩ��
      //m_C = 10;// �����е�˽��Ȩ���Ա ������ʲ���
	}
};

void test02()
{
	Son2 s2;
	//s2.m_A = 100;//�� son2 �и���Ĺ���Ȩ�޳�Ա ��Ϊ����Ȩ�� ������ʲ���
	//s2.m_B = 100; 
}

//˽�м̳�
class Baese3
{
public:
	int m_A;
protected:
	int m_B;
private:
	int m_C;
};

class Son3:private Baese3
{
private:

	void func()
	{
		m_A = 10;//�����еĹ���Ȩ�޳�Ա �������Ϊ˽��Ȩ��
		m_B = 10;//�����еı���Ȩ�޳�Ա �������Ϊ˽��Ȩ��
		//m_C = 10;//�����е�˽��Ȩ�޳�Ա ������ʲ���
	}
};

void test03()
{
	Son3 s3;
	//s3.m_A = 100;//�� Son3�� �����еĹ���Ȩ�޳�Ա ��Ϊ˽��Ȩ�� ������ʲ���
	//s3.m_B = 100;//
}

int main()
{
	
	

	system("pause");
	return 0;
}