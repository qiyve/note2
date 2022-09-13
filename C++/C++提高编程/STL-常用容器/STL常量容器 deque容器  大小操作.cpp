#include<iostream>
using namespace std;
#include<deque>

// deque������С����

//deque.empty();       //�ж������Ƿ�Ϊ��
//deque.size();        //����������Ԫ�صĸ���
//deque.resize(num);   //����ָ�������ĳ���Ϊnum���������䳤������Ĭ��ֵ���
					   //���������̣���ĩβ�����������ȵ�Ԫ�ر�ɾ����
//deque.resize(num, elem);//����ָ����������Ϊnum���������䳤������elemֵ�����λ��
						  //����������ȱ�̣���ĩβ�����������ȵ�Ԫ�ر�ɾ��

void printDeque(const deque<int>& d)
{ 
	  //������޶�����ֻ��״̬    ���� const_iterator ֻ��������   
	for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++)
	{
		//*it=100; ���������ݲ������޸���
		
		cout << *it << " ";
	}
	cout << endl;
}

void test01()
{
	deque<int>d;
	for (int i = 0; i < 10; i++)
	{
		d.push_back(i);
	}
	printDeque(d);

	if (d.empty()) //Ϊ��  ����Ϊ��
	{
		cout << "����Ϊ��" << endl;
	}
	else
	{
		cout << "������СΪ��" << d.size() << endl;
	}

	//����ָ��������С
	//d.resize(15);  ������������䳤������Ĭ��ֵ���
	d.resize(5);
	printDeque(d);

}



int main()
{

	test01();

	

	system("pause");
	return 0;
}