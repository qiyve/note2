#include<iostream>
using namespace std;

//��̬�Ļ�������

//������
class Animal
{
public:
   // �麯��  �ؼ��� vritual 
	virtual void speak()
	{
		cout << "������˵��" << endl;
	}
};

//è��
class Cat :public Animal
{
public:
	void speak()
	{
		cout << "Сè��˵��" << endl;
	}
};

//����
class Dog:public Animal
{
public:

	void speak()
	{
		cout << "С����˵��" << endl;
	}
};

//ִ��˵������
//��ַ���  �ڱ���׶�ȷ��������ַ
//�����ִ����è˵������ô���������ַ�Ͳ�����ǰ����Ҫ�����н׶ν��а󶨣� ��ַ���
void doSpeak(Animal &animal) // Animal & animal = cat;
{
	animal.speak();
}

void test01()
{
	Cat cat;
	doSpeak(cat);

	Dog dog;
	doSpeak(dog);
}
int main()
{

	test01();

	system("pause");
	return 0;
}