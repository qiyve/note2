#include <stdio.h>

int main01()
{
	//�������� �������� ������[Ԫ�ظ���] = {ֵ1��ֵ2....};
	//����ָ������ 
	int a = 10;
	int b = 20;
	int c = 30;

	int* arr[3] = { &a,&b,&c };
	//printf("%d\n", *arr[0]);
	for (int i = 0; i < 3; i++)
	{
		printf("%d\n", *arr[i]);
	}

	printf("ָ�������С��%d\n", sizeof(arr));
	printf("ָ��Ԫ�ش�С��%d\n", sizeof(arr[0]));


	system("pause");
	return 0;
}

int main()
{
	//ָ����������Ԫ�ش洢����ָ��
	int a[] = { 1,2,3 };
	int b[] = { 4,5,6 };
	int c[] = { 7,8,9 };
	//ָ��������һ������Ķ�ά�����ģ��
	int* arr[] = { a,b,c };
	//printf("%p\n", arr);
	//printf("%p\n", &arr[0]);

	//printf("%d\n", arr[1][1]);
	
	//printf("%p\n", arr[0]);
	//printf("%p\n", a);
	//printf("%p\n", &a[0]);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			//��ά����
			//printf("%d ", arr[i][j]);
			//printf("%d ", *(arr[i] + j)); //j��ʾƫ����
			printf("%d ", *(*(arr + i) + j));

		}
		printf("\n");
	}

	return 0;
	
}