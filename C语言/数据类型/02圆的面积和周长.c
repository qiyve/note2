#include<stdio.h>
//�궨�峣��
#define PI 3.14159

//Բ����� s = pi * r * r
//Բ���ܳ� l = 2 * pi * r

int main()
{
	//����PI
	//cosnt �������� ������ = ֵ
	//const float pi = 3.14159;

	float r = 2.f;

	float s = PI * r * r;
	float l = 2 * PI * r;

	//ռλ�� %f ��ʾ���һ�������� float  Ĭ�ϱ�����λС��  ����������
	printf("Բ�������%.2f\n", s);
	printf("Բ���ܳ���%.2f\n", l);

	return 0;
}