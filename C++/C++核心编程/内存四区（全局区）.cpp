#include<iostream>
using namespace std;

//ȫ�ֱ���  �� ֻҪûд�ں������еı�������ȫ�ֱ���
int g_a = 10;
int g_b = 10;

//const ���ε�ȫ�ֱ���  ȫ�ֳ���

const int c_g_a = 10;
const int c_g_b = 10;

int main()
{
	//ȫ����
	
	//ȫ�ֱ����� ��̬����������


	//������ͨ�ֲ�����
	int a = 10;
	int b = 10;
	cout << "�ֲ�����a�ĵ�ַ��" << (int)&a << endl;//��(int)ǿת��ʮ����
	cout << "�ֲ�����b�ĵ�ַ��" << (int)&b << endl;

	//ȫ�ֱ�����ַ
	cout << "ȫ�ֱ���g_a�ĵ�ַ" << (int)&g_a << endl;
	cout << "ȫ�ֱ���g_b�ĵ�ַ" << (int)&g_b << endl;

	//��̬����   ����ͨ����ǰ���static�����ھ�̬����
	static int s_a = 10;
	static int s_b = 20;

	cout << "��̬����s_a�ĵ�ַ" << (int)&s_a << endl;
	cout << "��̬����s_b�ĵ�ַ" << (int)&s_b << endl;


	//����
	//�ַ�������
	
	cout << "hello world�ĵ�ַ" << (int)&"hello world" << endl;

	//const���εı���
	//const���ε�ȫ�ֱ���   const���εľֲ�����


	//const���ε�ȫ�ֱ���   ȫ�ֳ���

	cout << "ȫ�ֳ���c_g_a�ĵ�ַ" << (int)&c_g_a << endl;
	cout << "ȫ�ֳ���c_g_b�ĵ�ַ" << (int)&c_g_b << endl;


	//const���εľֲ�����   �ֲ�����
	const int c_l_a = 10; //c-const  g-global(ȫ��)   l-local���ֲ���
	const int c_l_b = 10;
	
	cout << "�ֲ�����c_l_a��ַ" << (int)&c_l_a << endl;
	cout << "�ֲ�����c_l_b��ַ" << (int)&c_l_b << endl;

	//c++���ڳ�������ǰ��Ϊȫ�����ʹ�����
	// �������ص��ǹ����ֻ��
	// ȫ�����д��ȫ�ֱ�������̬����������
	// �������д��const���ε�ȫ�ֳ������ַ�������


	system("pause");
	return 0;
}