#include<iostream>
using namespace std;

//��ӡ���  ���÷�ʽ���� ��������ʵ��
//���� const ��ɳ�������  ��ֹ�����
void showValue(const int& val)
{
	//val = 1000;   ����const ֮���Ϊֻ�����������޸�

	cout << "val= " << val << endl;
}

int main()
{
	//��������
	//ʹ�ó����� ���������βΣ� ��ֹ�����
	
	int b = 10;

	//���� const֮�󣬱������������޸� int temp = 10; const int & ret= temp;
	const int &ret = 10;//���ñ�����һ��Ϸ����ڴ��

	//ret = 20;//����const ֮���Ϊֻ�����������޸�


	//���������ó������÷�ֹ������޸�ʵ��
	int a = 10;

	showValue(a);
	cout << "a= " << a << endl;


	system("pause");
	return 0;

}