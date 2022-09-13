#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>


//���ñ����㷨 for_each

//for_each(iterator beg, interator end, _func);
//�����㷨��������Ԫ��
//beg��ʼ������
//end����������
//_func�������ߺ�������

//��ͨ����
void Print(int val)
{
	cout << val << " ";
}
//�º���
class Print02
{
public:

	void operator()(int val)
	{
		cout << val << " ";
	}
};

void test01()
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}

	for_each(v.begin(), v.end(), Print);
	cout << endl;


	for_each(v.begin(), v.end(), Print02());
	cout << endl;
}


int main()
{
	test01();
	

	system("pause");
	return 0;
}