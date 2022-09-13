
#include <iostream>
using namespace std;
//2���������� ð������  ����1 ������׵�ַ�� ����2 ����ĳ���
void bubbleSort(int *arr, int len)
{
	//���ѭ������ ���� = ���鳤�ȣ�len�� -1
	for(int i=0;i<len;i++)
	{  
		//�ڲ�ѭ������  ���� = Ԫ�س���(len) - ���� -1 
		for (int j = 0; j < len - i - 1; j++)
		{
		//��� j > j+1��ֵ  ��������
			if (arr[j] > arr[j+1])
			{
				int temp = arr[j];
				arr[j ]=arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}
//��ӡ�������
void printArray(int* arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << endl;
	}
}

int main()
{
	//1.��������
	int arr[9] = { 7,6,2,1,3,4,9,5,8 };

	//���鳤��
	int len = sizeof(arr) / sizeof(arr[0]);
	
	//2���������� ʵ��ð������
	bubbleSort(arr, len);

	//3����ӡ���
	printArray(arr, len);


	system("pause");
	return 0;
}
