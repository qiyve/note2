#include<iostream>
using namespace std;
#include<queue>
#include<string>

//����queue ���� ���ýӿ�

//���캯����
//queue<T>que;       //queue����ģ����ʵ�֣�queue�����Ĭ�Ϲ�����ʽ
//queue��const queue& que���� //�������캯��

//��ֵ������
//queue& operator= (const queue& que);  //���صȺ������

//���ݴ�ȡ��
//push(elem);             //�Ӷ�β���Ԫ��
//pop������               //�Ӷ�ͷ�Ƴ���һ��Ԫ��
//back������              //�������һ��Ԫ��
//front ������             //���ص�һ��Ԫ��

//��С������
//emptm����;             //�ж϶�ջ�Ƿ�Ϊ��
//size������                //����ջ�Ĵ�С

class Person
{
public:

	Person(string name, int age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

	string m_Name;
	int m_Age;
};

void test01()
{
	//��������
	queue<Person>q;

	//׼������
	Person p1("��ɮ", 20);
	Person p2("�����", 22);
	Person p3("��˽�", 26);
	Person p4("ɳ����", 25);

	//���
	q.push(p1);
	q.push(p2);
	q.push(p3);
	q.push(p4);

	cout << "���д�Сλ��" << q.size() << endl;

	//�ж϶��в�Ϊ�գ��鿴��ͷ��β������
	while (!q.empty())
	{
		//�鿴��ͷ
		cout << "��ͷԪ��---������" << q.front().m_Name << " ���䣺" << q.front().m_Age << endl;

		//�鿴��β
		cout << "��βԪ��---������" << q.back().m_Name << " ���䣺" << q.back().m_Age << endl;

		//����
		q.pop();
	}

	//�鿴��С
	cout << "���еĴ�Сλ��" << q.size() << endl;
}

//�ܽ᣺  ��� --- push
//        ���� --- pop
//    ���ض�ͷ --- front
//    ���ض�β --- back
//�ж��Ƿ�Ϊ�� --- empty
//  ����ջ��С --- size()

int main()
{
	test01();
	

	system("pause");
	return 0;
}