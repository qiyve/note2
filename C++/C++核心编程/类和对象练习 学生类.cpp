#include<iostream>
using namespace std;
#include<string>


//���һ��ѧ���࣬���ԣ����� ����ѧ��
// ���Ը�������ѧ�Ÿ�ֵ��������ʾѧ����������ѧ��


//ѧ����
//class �������һ���࣬���������ŵľ���������
class Student
{
	//����Ȩ��
public://����Ȩ��

	//���е����Ժ���Ϊ������ͳһ��Ϊ ��Ա
	//����  ��Ա����  ��Ա����
	//��Ϊ  ��Ա����  ��Ա����


	//����
	string m_Name;//����
	int m_ID;//ѧ��

	//��Ϊ
	//��ʾ������ѧ��
	void showStudent()
	{
		cout << "������" << m_Name << "ѧ�ţ�" << m_ID << endl;
	}
	//��������ֵ
	void setName(string name)
	{
		m_Name = name;
	}
	//��ѧ�Ÿ�ֵ
	void setID(int id)
	{
		m_ID = id;
	}
};
int main()
{
	//����һ������ѧ��
	Student s1;
	//��s1���� �������Ը�ֵ
	
	//s1.m_Name = "����";
	s1.setName("����");
	//s1.m_ID=1;
	s1.setID(1);

	//��ʾѧ����Ϣ
	s1.showStudent();

	Student s2;
	s2.m_Name = "����";
	s2.m_ID = 10;

	s2.showStudent();

	system("pause");
	return 0;
}