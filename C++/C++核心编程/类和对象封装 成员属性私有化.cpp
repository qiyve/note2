#include<iostream>
using namespace std;
#include<string>

//��Ա��������Ϊ˽��
//1�������Լ����ƶ�дȨ��
//2������дȨ�ޣ����ǿ��Լ�����ݵ���Ч��

//�������
class Person
{
public:

	//��������  �ɶ���д
	void setName(string name)
	{
		m_Name = name;
	}
	//��ȡ����
	string getName()
	{
		return m_Name;
	}

	//��ȡ����  ֻ�� 
	int getAge()
	{
		//m_Age = 0;//��ʼ��Ϊ0�� 
		return m_Age;
	}
	//�������� 
	void setAge(int age)
	{
		if (age < 0 || age>150)
		{
			m_Age = 0;
			cout << "�����������" << endl;

			return;
		}
		m_Age = age;
	
	}
	//�������� ֻд
	void setLover(string lover)
	{
		m_Lover = lover;
	}
private:
    //����  �ɶ���д
	string m_Name;

	//����  ֻ��
	int m_Age;

	//����  ֻд
	string m_Lover;

};
int main()
{
   //�����������
	Person p;

	//�������� �ɶ���д
	p.setName ("����");

	cout << "����Ϊ:" << p.getName() << endl;
	
	//��������  ֻ��
	//p.m_Age = 18;// ���� 
	//p.m_Age(18);// ����  
	cout << "����Ϊ;" << p.getAge() << endl;

	//��������  �ɶ���д
	p.setAge (100);
	cout << "����Ϊ;" << p.getAge() << endl;
	
    //��������  ֻд
	p.setLover("����");
	//cout << "�������� ��" << p.setLover << endl;//��ֻдȨ��


	system("pause");
	return 0;
}