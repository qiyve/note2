#include<iostream>
using namespace std;
#include<string>

// �������ͳ�������

class Animal
{
public:
	Animal()
	{
		cout << "Animal���캯������" << endl;
	}
	~Animal()
	{
		cout << "Animal��������������" << endl;
	}
	//���麯��
	virtual void speak() = 0;
	
};

class Cat :public Animal
{
public:
	//è�Ĺ��캯��
	Cat(string name)
	{
		cout << "Cat���캯������" << endl;
		m_Name = new string(name);
	}
	virtual void speak()
	{
		cout << *m_Name<<"Сè��˵��" << endl;
	}

	~Cat()
	{
		
		if (m_Name != NULL)
		{
			cout << "Cat������������" << endl;
			delete m_Name;
			m_Name = NULL;
		}
	}

	string * m_Name;
};

void test01()
{
	Animal* animal = new Cat("Tom");
	animal->speak();
	delete animal;//�ͷ�
}
int main()
{

	test01();

	system("pause");
	return 0;
}