#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>

//�º��� ����ֵ������bool�������� ��Ϊν��
//���operator()����һ����������ô����һԪν��
//���operator()����������������ô������Ԫν��

//ν�� һԪν��

class GreaterFive
{
public:

	bool operator()(int val)
	{
		return val > 5;
	}
};

void test01()
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	//���������� ��û�д���5������
	//GreaterFive() ������������
	vector<int>::iterator it = find_if(v.begin(), v.end(), GreaterFive());

	if (it == v.end())
	{
		cout << "δ�ҵ�����5������" << endl;
	 }
	else
	{
		cout << "�ҵ�����5�����֣�" << *it << endl;
	}
}


int main()
{
	test01();


	system("pause");
	return 0;
}