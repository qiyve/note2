#include<iostream>
using namespace std;
#include<vector>

// vector  �����ʹ�С

// empty��);                 // �ж������Ƿ�Ϊ��
// capacity������            // ��������
// size������                // ����������Ԫ�صĸ���
// resize��int  num ����     // {���¶��������ĳ���Ϊnum���������߳�������Ĭ��ֵ�����λ��
						     // ���������̣���ĩβ�����������ȵ�Ԫ�ر�ɾ��}

///resize ��int num��elem); // {���¶�����������Ϊnum���������䳤������elemֵ�����λ��
							// ���������̣���ĩβ�����������ȵ�Ԫ�ر�ɾ��}

void printVector(vector<int>& v)
{
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

// vector���� �����ʹ�С��ϵ ������ ���ڵ��� ��С
void test01()
{
	vector<int>v1;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
	}
	printVector(v1);
	
	if (v1.empty()) //Ϊ��  ��������Ϊ��
	{
		cout << "v1 Ϊ��" << endl;
	}
	else
	{
		cout << "v1 ��Ϊ��" << endl;
		cout << "v1������Ϊ��" << v1.capacity() << endl;
		cout << "v1�Ĵ�С:" << v1.size() << endl;
	}

	//����ָ����С
	//v1.resize(20); //������¶���ı�ԭ�����ˣ�Ĭ����0���
    v1.resize(20, 10); //�������ذ汾������ָ��Ĭ�����ֵ������2
	printVector(v1);

	v1.resize(5);  //������¶���ı�ԭ�����ˣ�ɾ��ĩβ����Ԫ��
	printVector(v1);
}



int main()
{

	test01();


	system("pause");
	return 0;
}