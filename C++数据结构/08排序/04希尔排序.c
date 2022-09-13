#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include<sys\timeb.h>

#define MAX 30000

//��¼ʱ��
long getSystemTime()
{
	struct timeb tb;
	ftime(&tb);
	
	return tb.time * 1000 + tb.millitm;
}

//ϣ������  ��С����
void ShellSort(int arr[], int len)
{
	//����
	int increasement = len;
	int i, j, k;
	do
	{
		//ȷ����������
		increasement = increasement / 3 + 1;
		
		//ȷ��ÿһ��ĵ�һ��Ԫ��
		for (i = 0; i < increasement; i++)
		{
			//������ǰһ��
			for (j = i + increasement; j < len; j += increasement)
			{
				if (arr[j] < arr[j - increasement])
				{
					int temp = arr[j]; //���� 
					for (k = j - increasement; k >= 0 && temp < arr[k]; k -= increasement)
					{
						arr[k + increasement] = arr[k]; //�ƶ�
					}
					arr[k + increasement] = temp;//����

				}
			}
		}
	} while (increasement > 1);

}

//��������
void InsertSort(int arr[], int len)
{
	int j;
	for (int i = 1; i < len; i++)
	{
		if (arr[i] < arr[i - 1])
		{
			int temp = arr[i];//���浱ǰλ�õ�ֵ

			//����������ǰ�ƶ�
			for (j = i - 1; j >= 0 && temp < arr[j]; j--)
			{
				//�ƶ�
				arr[j + 1] = arr[j];
			}
			arr[j + 1] = temp; 
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

	//PrintArray(arr, MAX);
	//ShellSort(arr, MAX);
	//PrintArray(arr, MAX);

	//ϣ������Ͳ�����������ʱ��
	long tshell_start = getSystemTime();
	ShellSort(arr, MAX);
	long tshell_end = getSystemTime();
	printf("ϣ������%d��Ԫ�أ�����ʱ�䣺%d\n", MAX, tshell_end - tshell_start);

	long tinsert_start = getSystemTime();
	InsertSort(arr2, MAX);
	long tinsert_end = getSystemTime();
	printf("��������%d��Ԫ�أ�����ʱ�䣺%d\n", MAX, tinsert_end - tinsert_start);



	system("pause");
	return 0;
}