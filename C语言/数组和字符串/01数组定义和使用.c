#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int main01()
{
	//��������
	//�������� ����  = ֵ
	//���鶨��
	//�������� ������[Ԫ�ظ���] = {ֵ1��ֵ2��ֵ3}
	int arr[10] = { 9,5,8,7,6,1,4,2,3,10 };

	//�����±� ��0��ʼ  ������[�±�]
	//�����±��Ǵ�0��ʼ�ĵ�����Ԫ�ظ��� - 1	
	//printf("%d\n", arr[0]);
	for (int i = 0; i < 10; i++)
	{
		printf("%d\n", arr[i]);
	}

	system("pause");
	return 0;
}
int main02()
{
	//����Ԫ�ز������
	int arr[5] = { 1,2,3,4,5, };
	arr[0] = arr[4];
	for (int i = 0; i < 5; i++)
	{
		printf("%d\n", arr[i]);
	}
	
	return 0;
}

int main()
{
	 //�������ڴ��д洢��ʽ�ʹ�С
	int arr[5] = { 1,2,3,4,5 };

	//�±�Ϊ0��Ԫ�ص�ַ ��ַ�� %p
	printf("%p\n", &arr[0]);
	//printf("%p\n", &arr[1]); 
	//printf("%p\n", &arr[2]);
	//printf("%p\n", &arr[3]);
	//printf("%p\n", &arr[4]);

	//��������һ����ַ���� ָ�������׵�ַ�ĳ���
	printf("%p\n", arr);

	//��С �������ڴ���ռ�Ĵ�С = �������� * Ԫ�ظ���
	printf("�������ڴ���ռ�Ĵ�С��%d\n", sizeof(arr));
	printf("����Ԫ�ش�С��%d\n", sizeof(arr[0]));
	printf("����Ԫ�ظ�����%d\n", sizeof(arr) / sizeof(arr[0]));

	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		printf("%d\n", arr[i]);
	}

	return 0;
}