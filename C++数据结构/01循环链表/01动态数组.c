#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include"DynamicArray.h"

void test01()
{
//��ʼ����̬�������
	Dynamic_Array* myArray = Init_Array();
	//��ӡ��С 	����
	printf("�����С%d\n", Size_Array(myArray));
	printf("����������%d\n", Capacity_Array(myArray));
	//����Ԫ��
	for (int i = 0; i < 20; i++)
	{
		PushBack_Array(myArray, i);
	}

	//ɾ��
	/*RemoveByPos_Array(myArray, 5); λ��
	RemoveByValue_Array(myArray, 2); ֵ */
	//��ӡ
	Print_Array(myArray);

	//���ҵ�10��λ��
	int pos = Find_Array(myArray, 5);
	printf("10��λ�ò鵽��pos:%d %d\n", pos, At_Array(myArray, pos));

	//�ͷ�
	FreeSpace_Array(myArray);

}

int main()
{
	test01();

	return 0;
}