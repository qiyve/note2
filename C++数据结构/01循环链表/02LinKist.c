#include"02LinKist.h"


//��ʼ������
LinkList* Init_LinkList()
{
	LinkList* list = (LinkList*)malloc(sizeof(LinkList));
	list->size = 0;

	//ͷ�ڵ� �ǲ�����������Ϣ
	list->head = (LinkNode*)malloc(sizeof(LinkNode));
	list->head->data = NULL;
	list->head->next = NULL;

	return list;
}
//ָ��λ�ò���
void Insert_LinkList(LinkList* list, int pos, void* data)
{
	if (list == NULL)
	{
		return;
	}
	if (data == NULL)
	{
		return;
	}

	//�Ѻô���,posԽ��  Ĭ�ϲ���β��
	if (pos<0 || pos>list->size)
	{
		pos = list->size;
	}

	//�����µĽ��
	LinkNode* newnode = (LinkNode*)malloc(sizeof(LinkNode));
	newnode->data = data;
	newnode->next = NULL;

	//�ҽڵ�
	//����ָ�����
	LinkNode* pCurrent = list->head;
	for (int i = 0; i < pos; i++)
	{
		pCurrent = pCurrent->next;
	}

	//�½ڵ�������
	newnode->next = pCurrent->next;
	pCurrent->next = newnode;

	list->size++;
}
//ɾ��ָ��λ�õ�ֵ
void RemoveByPos_LinkList(LinkList* list, int pos)
{
	if (list == NULL)
	{
		return;
	}
	if (pos<0 || pos>list->size)
	{
		return;
	}

	//����ǰɾ������ǰһ�����
	LinkNode* pCurrent = list->head;
	for (int i = 0; i < pos; i++)
	{
		pCurrent = pCurrent->next;
	}

	//����ɾ���ļ��
	LinkNode* pDel = pCurrent->next;
	pCurrent->next = pDel->next;
	//ɾ���ڵ��ڵ��ڴ�
	free(pDel);

	list->size--;
}
//���������
int Size_LinkList(LinkList* list)
{
	return list->size;
}

//����
int Find_LinkList(LinkList* list, void* data)
{
	if (list == NULL)
	{
		return -1;
	}
	if (data == NULL)
	{
		return-1;
	}

	//��������
	LinkNode* pCurrent = list->head->next;
	int i = 0; //��¼λ�� 
	while (pCurrent != NULL)
	{
		if (pCurrent->data == data)
		{
			break;
		}
		pCurrent = pCurrent->next;
		i++;
	}

	return i;
}

//���ص�һ�����
void* Front_LinkList(LinkList* list)
{
	return list->head->next->data;
}

//��ӡ������
void Preint_LinkList(LinkList* list, PRINTLINKNODE print)
{
	if (list == NULL)
	{
		return;
	}

	//����ָ�����
	LinkNode* pCurrent = list->head->next;
	while (pCurrent != NULL)
	{
		print(pCurrent->data);
		pCurrent = pCurrent->next; //ƫ��
	}

}

//�ͷ�������ڴ�
void FreeSpace_LinkList(LinkList* list)
{
	if (list == NULL)
	{
		return;
	}

	//����ָ�����
	LinkNode* pCurrent = list->head;
	while (pCurrent != NULL)
	{
		//������һ�����
		LinkNode* pNext = pCurrent->next;
		free(pCurrent);
		pCurrent = pNext;
	}
	//�ͷ��б��ڴ�
	free(list);
	list->size = 0;
}
