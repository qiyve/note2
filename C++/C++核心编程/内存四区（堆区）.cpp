#include<iostream>
using namespace std;


int *func()
{
	///���ùؼ���new�����Խ����ݿ��ٵ�����
	//ָ�� ����Ҳ�Ǿֲ�����������ջ�ϣ�ָ�뱣��������Ƿ��ڶ���

	int* p = new int(100);//new int��100�����ص��Ƕ��������ĵ�ַ��Ȼ����ָ��ȥ����

	return p;
}
int main()
{

	//�ڶ�����������
	int* p = func();
	cout << *p << endl;
	cout << *p << endl;



	system("pause");
	return 0;
}