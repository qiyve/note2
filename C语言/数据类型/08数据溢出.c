#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>	


int main()
{
	//�������
	/*������һ�����������ܹ�������ķ�Χʱ����ֵ�������
	  �з���λ���λ��������𣺷���λ����ᵼ���������������ı䣬
	  �����λ������ᵼ�����λ��ʧ*/
	char ch = 127;
	ch = ch + 2;
	printf("%d\n", ch);

	return 0;
}