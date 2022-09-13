#include<iostream>
using namespace std;
#include<string>

//�ֱ�������ͨд���Ͷ�̬����ʵ�ּ�����

//��ͨд��
class Calculator
{
public:

	int getResult(string oper)
	{
		if (oper == "+")
		{
			return m_num1 + m_num2;
		}
		else if (oper == "-")
		{
			return m_num1 - m_num2;
		}

		else if (oper == "*")
		{
			return m_num1 * m_num2;
		}
		return 0;
	}
	//�����Ҫ��չ�µĹ��ܣ���Ҫ�޸�Դ��
	//����ʵ�����У��ᳫ ����ԭ��
	//����ԭ�� ������չ���п��������޸Ľ��йر�

	int m_num1;//������1
	int m_num2;//������2
};

void test01()
{
	//�����������Ķ���
	Calculator c;
	c.m_num1 = 100;
	c.m_num2 = 100;
	//�ӷ�
	cout << c.m_num1 << "+" << c.m_num2 << "=" << c.getResult("+") << endl;
	//����
	cout << c.m_num1 << "-" << c.m_num2 << "=" << c.getResult("-") << endl;
	//�˷�
	cout << c.m_num1 << "*" << c.m_num2 << "=" << c.getResult("*") << endl;
}

//���ö�̬ʵ�ּ�����

//ʵ�ּ����������
class AbstractCalculator
{
public:

	virtual int getResult()
	{
		return 0;
	}

	int m_num1;
	int m_num2;
};

//�ӷ��ӷ���������
class AddCalculator :public AbstractCalculator
{
	//���� virtual ��д�ɲ�д
	virtual int getResult()
	{
		return m_num1 + m_num2;
	}
};

//����������������
class SubCalculator :public AbstractCalculator
{
	virtual int getResult()
	{
		return m_num1 - m_num2;
	}
};

//�˷���������
class MulCalculator :public AbstractCalculator
{
	virtual int getResult()
	{
		return m_num1 * m_num2;;
	}
};

void test02()
{
	//��̬ʹ������
	//����ָ���������ָ���������

	//�ӷ�����
	AbstractCalculator* abc = new AddCalculator;
	abc->m_num1 = 30;
	abc->m_num2 = 20;

	cout << abc->m_num1 << "+" << abc->m_num2 << "=" << abc->getResult() << endl;
	//�����ǵ�����
	delete abc;

	//��������
	abc = new SubCalculator;
	abc->m_num1 = 30;
	abc->m_num2 = 20;

	cout << abc->m_num1 << "-" << abc->m_num2 << "=" << abc->getResult() << endl;
	delete abc;

	//�˷�����
	abc = new MulCalculator;
	abc->m_num1 = 30;
	abc->m_num2 = 20;

	cout << abc->m_num1 << "*" << abc->m_num2 << "=" << abc->getResult() << endl;
	delete abc;


}
int main()
{

	//test01();

	test02();


	system("pause");
	return 0;
}