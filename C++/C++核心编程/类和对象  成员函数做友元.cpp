#include<iostream>
using namespace std;
#include<string>

//��Ա��������Ԫ

//������
class Building;//�������������������

class GoodGay
{
public:

	GoodGay();

	void visit();//��visit ���Է���Building�е�˽�г�Ա

	void visit2();// �� visit2 �����Է���Building�е�˽�г�Ա

	Building* building;

};

class Building
{
	//��Ա����visit��Building������ ���Է���   �ӹؼ��� friend 
	friend void GoodGay::visit();

public:

	 Building();

public://����
	 
	string m_SttingRoom;//����

private://˽��

	string m_BedRoom;//����

};

//����д��Ա����
Building::Building()
{
	m_SttingRoom = "����";
	m_BedRoom = "����";
}

GoodGay::GoodGay()
{
	//���������Ķ���
	building = new Building;
}

void GoodGay::visit()
{
	cout << "�û���visit ���ڷ���:" << building->m_SttingRoom << endl;
	cout << "�û���visit ���ڷ��ʣ�" << building->m_BedRoom << endl;
}

void GoodGay::visit2()
{
	cout << "����visit2 ���ڷ���:" << building->m_SttingRoom << endl;

	// visit2 ����Building�ĺ����� ���Բ������Է���
	cout << "����visit2 ���ڷ��ʣ�" << building->m_BedRoom << endl;
}

//����
void test01()
{
	GoodGay gg;
	//gg.visit();
	gg.visit2();
	
}
int main()
{
	
	test01();

	system("pause");
	return 0;
}