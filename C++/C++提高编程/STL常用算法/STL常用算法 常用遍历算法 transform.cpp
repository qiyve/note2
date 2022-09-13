#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>


//���ñ����㷨 transform


//transform(itreator beg1, iterator end1, iterator beg2, _func);
//beg1 Դ������ʼ������
//end1 Դ��������������
//beg2 Ŀ��������ʼ������
//_func �������ߺ�������

class Transform
{
public:
	
	int operator()(int v)
	{
		return v+100;
	}
};

class MyPrint
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
	
	vector<int>vTarget;//Ŀ������
	vTarget.resize(v.size());//Ŀ��������Ҫ��ǰ���ٿռ�

	transform(v.begin(), v.end(), vTarget.begin(), Transform());
	
	for_each(vTarget.begin(), vTarget.end(), MyPrint());
	cout << endl;

}


int main()
{
	test01();
	

	system("pause");
	return 0;
}