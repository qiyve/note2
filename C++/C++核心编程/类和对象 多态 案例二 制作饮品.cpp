#include<iostream>
using namespace std;
#include<string>

//��̬������  ������Ʒ

//�������������
class AbstractDrinking
{
public:
	//��ˮ
	virtual void Boil() = 0;
	//����
	virtual void Brew() = 0;
	//���뱭��
	virtual void PourInCup() = 0;
	//���븨��
	virtual void PutSomething() = 0;

	//������Ʒ  ˳��
	void MakeDrink()
	{
		Boil();
		Brew();
		PourInCup();
		PutSomething();
	}
};

//��������
class Coffee :public AbstractDrinking
{
public:
	//��ˮ
	virtual void Boil()
	{
		cout << "�յ㿪ˮ" << endl;
	}
	//����
	virtual void Brew()
	{
		cout << "���ݿ���" << endl;
	}
	//���뱭��
	virtual void PourInCup()
	{
		cout << "���뱭��" << endl;
	}
	//���븨��
	virtual void PutSomething()
	{
		cout << "���뷽�Ǻ�ţ��" << endl;
	}
};

//���ݲ�ˮ
class Tea :public AbstractDrinking
{
public:
	//��ˮ
	virtual void Boil()
	{
		cout << "�յ㿪ˮ" << endl;
	}
	//����
	virtual void Brew()
	{
		cout << "���ݲ�Ҷ" << endl;
	}
	//���뱭��
	virtual void PourInCup()
	{
		cout << "������" << endl;
	}
	//���븨��
	virtual void PutSomething()
	{
		cout << "�����������" << endl;
	}
};

//��������
void doMake(AbstractDrinking * abs)
{
	abs->MakeDrink();

	delete abs;
}

void test01()
{
	//���ݲ�ˮ
	doMake(new Tea);

	cout << "----����������������" << endl;
   // ��������
	doMake(new Coffee);
}
int main()
{

	test01();

	system("pause");
	return 0;
}