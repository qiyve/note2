#include"DynamicArray.h"


//��̬�����ʼ��
Dynamic_Array* Init_Array()
{
	//�����ڴ� ???
	Dynamic_Array* myArray = (Dynamic_Array*)malloc(sizeof(Dynamic_Array));//����bug sizeof(Dynamic_Array*)
	//��ʼ��
	myArray->size = 0;
	myArray->capacity = 20;
	myArray->pAddr = (int*)malloc(sizeof(int) * myArray->capacity);

	return myArray;
}
//����
void PushBack_Array(Dynamic_Array* arr, int value)
{
	if (arr == NULL)
	{
		return;
	}

	//�жϿռ��Ƿ��㹻
	if (arr->size == arr->capacity)
	{
		//��һ�� ����һ�����Ŀռ� �¿ռ��Ǿɿռ��2��
		int* newSpace = (int*)malloc(sizeof(int) * arr->capacity * 2);
		//�ڶ��� �������ݵ��¿ռ�
		memcpy(newSpace, arr->pAddr, arr->capacity * sizeof(int));
		//������ �ͷžɿռ�
		free(arr->pAddr);

		//��������
		arr->capacity = arr->capacity * 2;
		arr->pAddr = newSpace;
	}

	//������Ԫ��
	arr->pAddr[arr->size] = value;
	//����Ԫ�ظ���
	arr->size++;
}

//����λ��ɾ��
void RemoveByPos_Array(Dynamic_Array* arr, int pos)
{
	if (arr == NULL)
	{
		return;
	}
	//�ж�λ���Ƿ���Ч
	if (pos < 0 || pos >= arr->size)
	{
		return;
	}

	//ɾ��Ԫ��
	for (int i = pos; i < arr->size - 1; i++)
	{
		arr->pAddr[i] = arr->pAddr[i + 1];
	}
	arr->size--;
}
//����ֵɾ��value ��һ�γ��ֵ�λ��
void RemoveByValue_Array(Dynamic_Array* arr, int value)
{
	if (arr == NULL)
	{
		return;
	}
	int pos = Find_Array(arr, value);
	//����λ��ɾ��
	RemoveByPos_Array(arr, pos);
}
//����
int Find_Array(Dynamic_Array* arr, int value)
{
	if (arr == NULL)
	{
		return -1;
	}
	//����
	int pos = -1;
	for (int j = 0; j < arr->size; j++)
	{
		if (arr->pAddr[j] == value)
		{
			pos = j;
			break;
		}
	}

	return pos;
}
//��ӡ
void Print_Array(Dynamic_Array* arr)
{
	if (arr == NULL)
	{
		return;
	}

	for (int i = 0; i < arr->size; i++)
	{
		printf("%d ", arr->pAddr[i]);
	}
	printf("\n");
}
//�ͷŶ�̬������ڴ�
void FreeSpace_Array(Dynamic_Array* arr)
{
	if (arr == NULL)
	{
		return;
	}

	if (arr->pAddr != NULL)
	{
		free(arr->pAddr);
	}
	free(arr);
}
//�������
void Clear_Array(Dynamic_Array* arr)
{
	if (arr == NULL)
	{
		return;
	}
	//pAdrr-> �ռ�
	arr->size = 0;

}
//��ȡ��̬��������
int Capacity_Array(Dynamic_Array* arr)
{
	if (arr == NULL)
	{
		return -1;
	}
	return arr->capacity;
}
//��ȡ��̬���鵱ǰԪ�ظ���
int Size_Array(Dynamic_Array* arr)
{
	if (arr == NULL)
	{
		return -1;
	}
	return arr->size;
}
//����λ�û�ȡĳ��λ�õ�Ԫ��
int At_Array(Dynamic_Array* arr, int pos)
{
	return arr->pAddr[pos];
}