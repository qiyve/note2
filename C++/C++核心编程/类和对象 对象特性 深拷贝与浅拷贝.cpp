#include<iostream>
using namespace std;


// �����ǳ����
//ǳ������ �򵥵ĸ��ƿ�������
//����� �ڶ�����������ռ䣬���п�������

class Person
{
public:
	Person() //Ĭ�Ϲ���
	{
		cout << "PersonĬ�Ϻ�������" << endl;
	}

	Person(int a,int height)//�вι���
	{
		m_Age = a;
		m_Height = new int(height);//���ٶ����ռ�

		cout << "Person�вι��캯���ĵ���" << endl;
		
	}

	Person(const Person& p)//��������
	{	
		cout << "Person�������캯���ĵ���" << endl;

		m_Age = p.m_Age;
		//m_Height = p.m_Height;������Ĭ��ʵ�־������д���

		//�������
		m_Height = new int(*p.m_Height);
	}

	~Person()
	{
		//�������룬�����������������ͷŲ���
		if (m_Height != NULL)
		{
			delete m_Height;
			m_Height = NULL;
		}
		cout << "Person�����������ĵ���" << endl;
	}
	int m_Age;//����
  // ���� * ����
	int* m_Height;//��� 
};

void test01()
{
	Person p1(18,160);

	cout << "p1�����䣺" << p1.m_Age <<"��ߣ�"<<*p1.m_Height<< endl;

	Person p2(p1);

	cout << "p2�����䣺" << p2.m_Age << "��ߣ�" << *p2.m_Height << endl;
}
//ǳ����������������Ƕ������ڴ��ظ��ͷ�
//ǳ�������ڴ� Ҫ����������н��
int main()
{
	
	test01();

	system("pause");
	return 0;
}