#include<stdio.h>

int main01()
{
	//�ƹ� 3Ԫ/��   ����5��
	//�������ڳ������й����У���ֵ���ܱ��ı���� ��Ϊ����
	
	const int price = 3; //���� ֻ������
	//price = 5;  err������

	//���� �ڳ������й����У���ֵ���Ըı� ��Ϊ����
	int weifht = 5;

	int sum = price * weifht;

	printf("%d\n", sum);
	return 0;
}