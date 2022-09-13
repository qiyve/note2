#include<iostream>
using namespace std;
#include<time.h>
#include<sys/timeb.h>

#define MAX 50000

long getSystemTime()
{
	struct timeb tb;
	ftime(&tb);
	return tb.time * 1000 + tb.millitm;
}

//��������
int* CreateArray()
{
	srand((unsigned int)time(NULL));
	int* arr = (int*)malloc(sizeof(int) * MAX);
	
	for (int i = 0; i < MAX; i++)
	{
		arr[i] = rand() % MAX;
	}

	return arr;
}

//��ӡ
void PrintArray(int arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << arr[i]<<" ";
	}
	cout << endl;
}
 
//�ϲ��㷨  ��С����
void Merge(int arr[], int start, int end, int mid, int* temp)
{
	//���������±߱���
	int i_start = start; //��һ���������п�ʼ
	int i_end = mid;  //����

	int j_start = mid + 1; //�ڶ� ͷ
	int j_end = end;      //β

	//��ʾ�����ռ��ж��ٸ�Ԫ��
	int len = 0;

	//�ϲ�������������
	while (i_start <= i_end && j_start <= j_end)
	{
		//�Ƚ�i��j  ��������ʱ�ڴ洢
		if (arr[i_start] < arr[j_start])
		{
			//i��ֵС�� j��ֵ
			temp[len] = arr[i_start];
			len++;   
			i_start++;
		}
		else
		{
			//i��ֵ >= j 
			temp[len] = arr[j_start];
			len++;
			j_start++;
		}
	}

	// �����������Ƿ�������  
	//i����
	while (i_start <= i_end)
	{
		temp[len] = arr[i_start];
		len++;
		i_start++;
	}
	// j����
	while (j_start <= j_end)
	{
		temp[len] = arr[j_start];
		len++;
		j_start++;
	}

	//�����ռ����ݸ���ԭ�ռ�
	for (int i = 0; i < len; i++)
	{
		arr[start + i] = temp[i];
	}
}

//�鲢����
void MergeSort(int arr[], int start, int end, int* temp)
{
	if (start >= end)
	{
		return;
	}

	int mid = (start + end) / 2;
	//����
	//����
	MergeSort(arr, start, mid, temp);
	//�Ұ��
	MergeSort(arr, mid + 1, end, temp);

	//�ϲ�
	Merge(arr, start, end, mid, temp);
}

int main()
{
	//��������
	int* arr = CreateArray();
	//�����ռ�
	int* temp = (int*)malloc(sizeof(int) * MAX);

	//PrintArray(arr, MAX);
	long t_start = getSystemTime();
	MergeSort(arr, 0, MAX - 1, temp);
	long t_end = getSystemTime();
	//PrintArray(arr, MAX);
	printf("����%d��Ԫ�أ���ȡʱ�䣺%d\n", MAX, t_end - t_start);

	//�ͷſռ�
	free(temp);
	free(arr);

	system("pause");
	return 0;
}