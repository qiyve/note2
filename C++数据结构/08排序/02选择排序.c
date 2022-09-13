#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include<sys\timeb.h>

#define MAX 2000

//��¼ʱ��
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


//ð������Ľ���
int flag = 0; //0 ��ʶ  û�������
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

//ѡ������
void SelectSrot(int arr[], int len)
{

	//ѡ���������Լ��ٽ�����������Ч��
	for (int i = 0; i < len; i++)
	{
		int min = i;
		for (int j = i + 1; j < len; j++)
		{
			//��ȡ��Сֵ�±�
			if (arr[j] < arr[min])
			{
				min = j;
			}
		}

		if (min != i)
		{
			Swap(&arr[min], &arr[i]);
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
	int arr2[MAX];
	srand((unsigned int)time(NULL));

	for (int i = 0; i < MAX; i++)
	{
		int randNum = rand() % MAX;
		arr[i] = randNum;
		arr2[i] = randNum;
	}

	//ѡ���������
	//PrintArray(arr, MAX);
	//SelectSrot(arr, MAX);
	//PrintArray(arr, MAX);

	//ð������
	long tbubble_start = getSystemTime();
	BubbleSort(arr, MAX);
	long tbubble_end = getSystemTime();
	printf("ð������%d��Ԫ�أ�����ʱ�䣺%1d\n", MAX, tbubble_end - tbubble_start);
	
	//ѡ������
	long tselect_start = getSystemTime();
	SelectSrot(arr2, MAX);
	long tselect_end = getSystemTime();
	printf("ð������%d��Ԫ�أ�����ʱ�䣺%1d\n", MAX, tselect_end - tselect_start);

	system("pause");
	return 0;
}