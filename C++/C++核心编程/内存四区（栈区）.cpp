#include<iostream>
using namespace std;

//ջ������ ע����� ��Ҫ���ؾֲ������ĵ�ַ
//ջ�������ɱ����������ٺ��ͷ�

int*func(int b)//�β�����Ҳ�����ջ��
{
	b = 100;

	int a = 10; //�ֲ�����
	return &a;//���ؾֲ������ĵ�ַ
}

int main()
{

	int* p = func();
	cout << *p << endl;//��һ�ο��Դ�ӡ��ȷ�ģ�����Ϊ���������˱���
	cout << *p << endl;//�ڶ���������ݾͲ��ٱ�����




	system("pause");
	return 0;
}