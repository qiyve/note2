#include<iostream>
using namespace std;

//���õı���
//���õ� ���ʾ���һ��ָ�볣��
//����һ����ʼ���󣬾Ͳ����Է����ı�

//���������ã�ת���� int * const ret = &a��
void func(int& ret)
{
	ret = 100; //ret �����ã�ת���� * ret = 100��
}

int main()
{
	int a = 10;

	/*�Զ�ת���� int* const ret = &a ��ָ�볣����ָ�� ָ�򲻿ɸģ�
	Ҳ˵��Ϊʲô���ò��ɸ��� */
	int& ret = a;

	ret = 20;//�ڲ������� ret ������ �Զ�ת���� * ret = 20��

	cout << "a= " << a << endl;
	cout << "ret= " << ret << endl;



	system("pause");
	return 0;
}