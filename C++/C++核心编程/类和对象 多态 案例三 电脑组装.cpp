#include<iostream>
using namespace std;
#include<string>

// ������ ������װ

//����ͬ�������
//����CPU��
class CPU
{
public:
    //������㺯��
	virtual void calculate() = 0;
};

//�����Կ���
class VideoCard
{
public:
	//������ʾ����
	virtual void display() = 0;
};

//�����ڴ�����
class Memory
{
public:
	//����洢����
	virtual void storage() = 0;
};

//�����������
class Computer
{
public:
	Computer(CPU *cpu,VideoCard *vc,Memory *mem)
	{
		m_cpu = cpu;
		m_vc = vc;
		m_mem = mem;
	}

	//�ṩ��������
	void word()
	{
		//������������������ýӿ�
		m_cpu->calculate();

		m_vc->display();

		m_mem->storage();
	}
	//�ṩ�������� �ͷ�3���������
	~Computer()
	{
		//�ͷ�CPU���
		if (m_cpu != NULL)
		{
			delete m_cpu;
			m_cpu = NULL;
        }

		//�ͷ��Կ����
		if (m_vc != NULL)
		{
			delete m_vc;
			m_vc = NULL;
		}

		//�ͷ��ڴ������
		if (m_mem != NULL)
		{
			delete m_mem;
			m_mem = NULL;
		}
	}

private:
	CPU * m_cpu;//CPU���ָ��
	VideoCard * m_vc;//�Կ����ָ��
	Memory * m_mem;//�ڴ������ָ��
};

//���峧��
//Intel ����
class IntelCPU :public CPU
{
public:
	virtual void calculate()
	{
		cout << "Intel��CPU���ڼ���" << endl;
	}
};

class IntelVideoCard :public VideoCard
{
public:
	virtual void display()
	{
		cout << "Intel���Կ�������ʾ" << endl;
	}
};

class IntelMemory :public Memory
{
public:
	virtual void storage()
	{
		cout << "Intel���ڴ������ڴ洢" << endl;
	}

};

//Lenovo����
class LenovoCPU : public CPU
{
public:
	virtual void calculate()
	{
		cout << "Lenovo��CPU���ڼ���" << endl;
	}
};

class LenovoVideoCard :public VideoCard
{
public:
	virtual void display()
	{
		cout << "Lenovo���Կ�������ʾ" << endl;
	}
};

class LenovoMemory :public Memory
{
public:
	virtual void storage()
	{
		cout << "Lenovo���ڴ������ڴ洢" << endl;
	}

};

void test01()
{
	//��һ̨�������
	CPU* intelCpu = new IntelCPU;
	VideoCard* intelvc = new IntelVideoCard;
	Memory* intelmem = new IntelMemory;

	//������һ̨����
	cout << "��һ̨��ʼ����" << endl;
	Computer* computer1 = new Computer(intelCpu, intelvc, intelmem);
	computer1->word();
	delete computer1;//�����ڴ��ֶ������ֶ��ͷ�

    //�ڶ�̨���� ��װ
	cout << "--������������������������--" << endl;
	cout << "�ڶ�̨��ʼ����" << endl;
	Computer* computer2 = new Computer(new LenovoCPU,new LenovoVideoCard,new LenovoMemory);
	computer2->word();
	delete computer2;

	//����̨������װ
	cout << "--������������������������--" << endl;
	cout << "����̨��ʼ����" << endl;
	Computer* computer3 = new Computer(new IntelCPU, new LenovoVideoCard, new IntelMemory);
	computer3->word();
	delete computer3;

}
int main()
{

	test01();

	system("pause");
	return 0;
}