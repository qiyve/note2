#include<iostream>
using namespace std;

//����Ĭ�ϲ���

//�﷨  ����ֵ���� ������ ���β� =Ĭ��ֵ��{ }
int func(int a = 10, int b = 20, int c = 30)
{
	return (a + b + c);
}

//��������Լ��������ݣ������Լ������ݣ����û����ô����Ĭ��ֵ
int func02(int a, int b=20 , int c = 40)
{
	return (a + b + c);
}

//ע������
//1�����ĳ��λ���Ѿ�����Ĭ�ϲ�������ô�����λ�����󣬴�(��ǰλ�ã����Ҷ�������Ĭ��ֵ

//int func(int a=10,int b,int c) //���� ĳ��λ������Ĭ�ϲ�������������Ҷ�������Ĭ��ֵ


//2�����������������Ĭ�ϲ���������ʵ�־Ͳ�����Ĭ�ϲ���
//������ʵ��ֻ����һ����Ĭ�ϲ���
int func03(int a = 10, int b = 10);

int func03(int a, int b)
{
	return (a + b);
}
int main()
{

	cout << func() << endl;

	cout << func02(20,30) << endl;

	cout << func03() << endl;

	system("pause");
	return 0;
}

