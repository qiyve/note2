#include<iostream>
using namespace std;

//�������� ����
void QuickSort(int arr[], int stack, int end)
{
	int i = stack;
	int j = end;

	//��׼��
	int temp = arr[stack];
	if (i < j)
	{
		while (i < j)
		{
			//�������� ȥ�ұȻ�׼��С��
			while (i < j && arr[j] >= temp)
			{
				j--;
			}
			//���
			if (i < j)
			{
				arr[i] = arr[j];
				i++;
			}

			//�������� �ұȻ�׼�������
			while (i < j && arr[i] < temp)
			{
				i++;
			}
			//���
			if (i < j)
			{
				arr[j] = arr[i];
				j--;
			}
		}

		//�ѻ�׼���ŵ� j �� i�ص���λ��
		arr[i] = temp;
        //����벿�ֽ��п�������
		QuickSort(arr, stack, i - 1);
		//���Ұ벿�ֽ��п�������
		QuickSort(arr, i + 1, end);

	}
}

void PrintArray(int arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << arr[i]<<" ";
	}
	cout << endl;
}

int main()
{
	int arr[] = { 4,2,8,0,5,7,1,3,9 };
	int len = sizeof(arr) / sizeof(int);
	PrintArray(arr, len);
	QuickSort(arr, 0, len - 1);
	PrintArray(arr, len);



	system("pause");
	return 0;
}