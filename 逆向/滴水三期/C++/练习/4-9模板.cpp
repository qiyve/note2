#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//����
template<class T>
void Swap(T& x,T &y)
{
	T temp;
	temp = x;
	x = y;
	y = temp;
}

//ð��
template<class T>
void Sort(T arr, int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				Swap(arr[j], arr[j + 1]);
			}
		}
	}
}

//�۰����
template<class T, class Y>
int MyFind(T arr, int len, Y Index)
{
	int begin = 0;  //��ʼ�±�
	int end = len - 1; //�����±�
	int num = 0;    // �����ж�

	while (begin <= end)
	{
		num = (begin + end) / 2; //( begin + end) >> 1
		if (arr[num] < Index)
		{
			begin = num + 1; // ������ �Ұ벿��
		}
		else if (arr[num] > Index)
		{
			end = num - 1; // ��벿��
		}
		else
		{
			return num; // �ҵ� ���ظ�ֵ �±�
		}

	}

	return -1; 
}

//����
void test()
{
	int arr[] = { 2,7,9,6,7,1,3,5 };

	for (int i = 0; i < 8; i++)
	{
		printf("%d ", arr[i]);
	}printf("\n");

	Sort(arr, 8);
	//for (int i = 0; i < 8; i++)
	//{
	//	printf("%d ", arr[i]);
	//}printf("\n");

	int x = MyFind(arr, 8, 9);
	printf("%d\n", x);
}

int main01()
{
	test();

	return 0;
}


class Person
{
public:

	int x;
	Person()
	{		x = 100;	}
};

void Test()
{
	Person p1, p2, p3, p4, p5;
	Person arr[] = { p1,p2,p3,p4,p5 };

	// Sort(arr, 5); err 
	//2��ð�����򣺶Խṹ���������������������ʵ�֣��ҳ���������.
	/* 
      ���� C2676	�����ơ�>��:��Person����������������Ԥ����������ɽ��յ����͵�ת��	

	   ԭ�򣺱����䲻֪������αȽϽṹ�弴��Ա�� ����취������ < �� > �����
	*/
}

int main()
{


	return 0;
}