//#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>	
#pragma warning (disable:4996)

int main(void)
{
	//int a;

	////ͨ���������븳ֵ
	////&����� ��ʾȡ��ַ�����
	//scanf("%d", &a);

	// ��� 5Ԫ/�� 

	const int price = 3; 

	int weight;
	printf("���������:\n");
	scanf("%d", &weight);

	int sum = price * weight;
	printf("%d\n", sum);
	
	return 0;
}

