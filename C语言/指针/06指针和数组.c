#include <stdio.h>


int main01()
{
	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	//��������һ������ ������ֵ
	// ��������������Ԫ�ص�ַ
	//arr = 100; //��
	int* p;
	p = arr;
	//printf("%p\n", p);
	//printf("%p\n", arr);

	*p = 123;
	//printf("%d\n", *p);
	//p++;

	//printf("%p\n", arr);
	//printf("%p\n", p);

	for (int i = 0; i < 10; i++)
	{
		//
		//printf("%d\n", *(arr + 1));//arr[1]
		//printf("%d\n", p[i]);
		//printf("%d\n", *(p + 1));
		printf("%d\n", *p++ );

	}

	//printf("%p\n", arr);
	//printf("%p\n", p);

	//����ָ����� �ȵ��Ľ��������ָ���ƫ����(����)
	//���е�ָ������ ����������int ����
	int step = p - arr; //3c +1= 40   �൱�� sizeof(int)  40/sizeof(int)

	printf("%d\n", step);

	system("pause");
	return 0;
}

int main02()
{
	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	//ָ�������ָ��
	int* p = arr;

	//p�Ǳ��� arr�ǳ���
	//p��һ����֯ 4���ֽڴ�С 
	//arr��һ������ 40���ֽڴ�С
	printf("ָ�����ʹ�С��%d\n", sizeof(p));
	printf("�����С��%d\n", sizeof(arr));


	//p[i];
	//*(p + i); iƫ����

	system("pause");
	return 0;
}


//������Ϊ�����������˻�Ϊָ�� ��ʧ����ľ���
void BubbleSort(int *arr,int len)
{
	int len = sizeof(arr) / sizeof(arr[0]);

	//printf("%d\n", sizeof(arr));

	for (int i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - 1 -i; j++)
		{
		/*	if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}*/
			if (*(arr + j) > *(arr + j + 1))
			{
				int temp = *(arr + j);
				*(arr + j) = *(arr + j + 1);
				*(arr + j + 1) = temp;
			}
		}
	}
}

int main()
{

	int arr[] = { 2,5,6,7,4,1,2,9,3,10 };

	BubbleSort(arr,10);
	for (int i = 0; i < 10; i++)
	{
		printf("%d\n", arr[i]);
	}

	system("pause");
	return 0;
}