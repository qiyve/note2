#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include<sys\timeb.h>

#define MAX 10

//��¼����
long getSystemTime()
{
	struct timeb tb;
	ftime(&tb);
	
	return tb.time * 1000 + tb.millitm;
}

//����
void Swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


int flag = 0; //0 ��ʶ  û�������
//ð������
void BubbleSort(int arr[], int len)
{
	for (int i = 0; i < len && flag == 0; i++)
	{
		flag = 1; //��Ϊ�Ѿ������
		for (int j = 0; j < len -i -1 ; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				flag = 0;
				Swap(&arr[j], &arr[j + 1]);
			}
		}
		
	}
}

//��ӡ
void PrintArray(int arr[],int len)
{
	for (int i = 0; i < len; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}


int main()
{
	int arr[MAX];
	srand((unsigned int)time(NULL));

	for (int i = 0; i < MAX; i++)
	{
		arr[i] = rand() % MAX;

	}

	printf("����ǰ\n");
	PrintArray(arr, MAX);
	long t_start = getSystemTime();
	printf("�����\n");
	BubbleSort(arr, MAX);
	long t_end = getSystemTime();
	printf("ð������%d��Ԫ�أ�����ʱ��:%1d\n", MAX, t_end - t_start);
	PrintArray(arr, MAX);

	system("pause");
	return 0;
}