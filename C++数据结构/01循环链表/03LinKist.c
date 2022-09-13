#include"03LinKist.h"


//��ʼ������
LinkList* Init_LinkList()
{
	LinkList* list = (LinkList*)malloc(sizeof(LinkList));
	list->size = 0;
	list->head.next = NULL;
	
	return list;
}
//����
void Insert_LinkList(LinkList* list, int pos, LinkNode* data)
{
	if (list == NULL)
	{
		return;
	}
	if (data == NULL)
	{
		return;
	}

	//���Խ��Ĭ�ϲ��뵽β��
	if (pos<0 || pos>list->size)
	{
		pos = list->size;
	}

	//���Ҳ���λ��
	LinkNode* pCurrent = &(list->head);
	for (int i = 0; i < pos; i++)
	{
		pCurrent = pCurrent->next;
	}

	//�����½ڵ�
	data->next = pCurrent->next;
	pCurrent->next = data;

	list->size++;
}
//ɾ��
void Remove_LinkList(LinkList* list, int pos)
{
	if (list == NULL)
	{
		return;
	}
	if (pos<0 || pos>=list->size)
	{
		return;
	}
	
	//����λ��
	LinkNode* pCurrent = &(list->head);
	for (int i = 0; i < pos; i++)
	{
		pCurrent = pCurrent->next;
	}

	pCurrent->next = pCurrent->next->next;

	list->size--;
}
//����
int Find_LinkList(LinkList* list, LinkNode* data, COMPARENODE compare)
{
	if (list == NULL)
	{
		return -1;
	}
	if (data == NULL)
	{
		return -1;
	}

	//����ָ�����
	LinkNode* pCurrent = list->head.next;
	int index = 0;
	while (pCurrent != NULL)
	{
		if (compare(pCurrent, data) == 0)
		{
			break;
		}

		pCurrent = pCurrent->next;
		index++;
	}


	return index;
}
//���������С
int Size_LinkList(LinkList* list)
{
	return list->size;
}
//��ӡ
void Print_LinkList(LinkList* list, PRINTNODE print)
{
	if (list == NULL)
	{
		return;
	}

	//����ָ��
	LinkNode* pCurrent = list->head.next;
	while (pCurrent != NULL)
	{
		print(pCurrent);
		pCurrent = pCurrent->next;//ƫ��
	}
}
//�ͷ������ڴ�
void FreeSpace_LinkList(LinkList* list)
{
	if (list == NULL)
	{
		return;
	}

	free(list);
}