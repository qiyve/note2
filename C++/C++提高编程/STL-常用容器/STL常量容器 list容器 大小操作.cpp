#include<iostream>
using namespace std;
#include<list>

//list���� ��ֵ�ͽ���

//size();              //����������Ԫ�صĸ���
//empty������          //�ж������Ƿ�Ϊ��
//resize();            //���¶��������ĳ���λ num���������䳤������Ĭ��ֵ�����λ��
					   //��������̣���ĩβ�����������ȵ�Ԫ�ر�ɾ��
//resize��num, elem��; //���¶��������ĳ���Ϊnum���������߳�������elemֵ�����λ��
					   //��������̣���ĩβ�����������ȵ�Ԫ�ر�ɾ��

void printList(const list<int>&L)
{    //�޶�ֻ��
	for (list<int>::const_iterator it = L.begin(); it != L.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

//��ֵ
void test01()
{
	list<int>L1; 

	//�������
	L1.push_back(10);
	L1.push_back(20);
	L1.push_back(30);
	L1.push_back(40);

	printList(L1);

	//�ж������Ƿ�Ϊ��
	if (L1.empty())
	{
		cout << "L1 Ϊ��" << endl;
	}
	else
	{
		cout << "L1 ��Ϊ��" << endl;
		cout << "L1��Ԫ�ظ�����" << L1.size() << endl; //������Ԫ�ظ���
	}

	//����ָ����С
	//L1.resize(10); //�����䳤 ��Ĭ��ֵ0 ���
	L1.resize(2);    //������� ɾ����������Ԫ�� 
	//10 20 
	printList(L1);

	//ָ��n��elem���
	L1.resize(10, 100);
	//10 20 100...
	printList(L1);
}

int main()
{
	test01();
	


	system("pause");
	return 0;
}