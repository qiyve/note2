
#include <iostream>
using namespace std;

int main()
{
	// 1��const����ָ��  --����ָ��
	
	int a = 10;
	int b = 20;

	const int* p = &a;
	
	//*p=20��  ����  ָ��ָ������޸ģ�ָ��ָ���ֵ�������޸�
	p = &b; //��ȷ

	// 2��const���γ���  --ָ�볣�� 
	
	int* const p2 = &b;
	

	*p2 = 100;//��ȷ
	//p2 = &a; ����  ָ��ָ�򲻿����޸ģ�ָ��ָ���ֵ�����޸�
	
	// 3��const������ָ�������γ��� 
	const int* const p3 = &a;

	//ָ���ָ���ָ��ָ���ֵ���������޸�

	//*p3 = 100;  ����
	//p3 = &b;    ����


	system("pause");
	return 0;
}
