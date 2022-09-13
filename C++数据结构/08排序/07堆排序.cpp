#include<iostream>
using namespace std;

void PrintArray(int arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

void MySwap(int arr[], int a, int b)
{
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

/*  �����ѵĺ���
    @param arr  ������������
	@param index �������Ľ���±�
	@param len  ����ĳ���  */
void HeapAdjust(int arr[], int index, int len)
{
	//�ȱ��浱ǰ�����±�
	int max = index;
	//�������Һ��ӵ����� �±�
	int lchild = index * 2 + 1;
	int rchild = index * 2 + 2;
    
	if (lchild<len && arr[lchild]>arr[max])
	{
		max = lchild;
	}
	if (rchild<len && arr[rchild]>arr[max])
	{
		max = rchild;
	}

	if (max != index)
	{
		//�����������
		MySwap(arr, max, index);
		HeapAdjust(arr, max, len);
	}
}

//������
void HeapSort(int arr[], int len)
{
	//1����ʼ���� �󶥶� ��С����
	for (int i = len / 2 - 1; i >= 0; i--)
	{
		HeapAdjust(arr, i, len);
	}

	//2�������Ѷ�Ԫ�غ����һ��Ԫ��
	for (int i = len - 1; i >= 0; i--)
	{
		MySwap(arr, 0, i); 
		HeapAdjust(arr, 0, i);
	}
	
}

int main()
{
	int arr[] = { 4,2,8,0,5,7,1,3,9 };
	int len = sizeof(arr) / sizeof(int);
	PrintArray(arr, len);
	//������
	HeapSort(arr, len);
	PrintArray(arr, len);


	system("pause");
	return 0;
}