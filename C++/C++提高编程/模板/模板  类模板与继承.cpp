#include<iostream>
using namespace std;
#include<string>

//��ģ����̳�

//1. ������̳еĸ�����һ��ģ��ʱ��������������ʱ����Ҫָ����������T������
//2. �����ָ�����������޷�������������ڴ�
//3. ��������ָ���������� T �����ͣ�����Ҳ��Ҫ��Ϊ��ģ��


template<class T>
class Base
{
public:

	T m;
};

//class Son:public Base //���󣬱���Ҫ֪�������е� T ����,���ܼ̳и�����
class Son1 :public Base<int>
{

};

void test01()
{
	Son1 s1;
}

//��������ָ��������T���ͣ�����Ҳ��Ҫ�����ģ��
template<class T1,class T2>
class Son2 :public Base<T2>
{
public:

	Son2()
	{
		cout << "T1 ���ͣ�" << typeid(T1).name() << endl;
		cout << "T2 ���ͣ�" << typeid(T2).name() << endl;
	}

	T1 obj;
};

void test02()
{
	Son2<int,string>  s2;
}
int main()
{
	test02();

	system("pause");
	return 0;
}