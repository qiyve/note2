#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>


//���ò����㷨  binary_search

//bool binary_search(iterator beg, iterator end, value);
//����ָ����Ԫ�� �鵽����true ���򷵻�false
//ע�⣺�� ���������в�����
//beg ��ʼ������
//end ����������
//value ���ҵ�Ԫ��

void test01()
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}

	v.push_back(2);
	//�����������Ƿ���6 Ԫ��
	//ע�⣺ �����б�������������� 
	bool ret = binary_search(v.begin(), v.end(), 6);

	if (ret)
	{
		cout << "�ҵ�Ԫ�أ�" << endl;
	}
	else
	{
		cout << "δ�ҵ�Ԫ��" << endl;
	}
}

int main()
{
	test01();
	

	system("pause");
	return 0;
}