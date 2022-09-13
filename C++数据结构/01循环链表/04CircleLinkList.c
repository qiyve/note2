#include"04CircleLinkList.h"



//��ʼ������
CircleLinkList* Init_CircleLinkList()
{
	CircleLinkList* clist =(CircleLinkList*) malloc(sizeof(CircleLinkList));
	clist->head.next = &(clist->head);
	clist->size = 0;
	return clist;
}
//���뺯��
void insert_CircleLinkList(CircleLinkList* clist, int pos, CircleLinkNode* data)
{
	if (clist == NULL)
	{
		return;
	}
	if(data==NULL)
	{
		return;
	}
	//�Ѻ��ж�
	if (pos < 0 || pos >= clist->size)
	{
		pos = clist->size;
	}

	//����λ�ò��ҽ��
	//����ָ�����
	CircleLinkNode* pCurrent = &(clist->head);
	for (int i = 0; i < pos; i++)
	{
		pCurrent = pCurrent->next;
	}

	//������������
	data->next = pCurrent->next;
	pCurrent->next = data;

	clist->size++;
}
//��õ�һ��Ԫ��
CircleLinkNode* Frond_CircleLinkList(CircleLinkList* clist)
{
	return clist->head.next;
}
//����λ��ɾ��
void RemovePos_CircleLinkList(CircleLinkList* clist, int pos)
{
	if (clist == NULL)
	{
		return;
	}
	if (pos < 0 || pos >= clist->size)
	{
		return;
	}
	//����pos�ҽ��
	//����ָ�����
	CircleLinkNode* pCurrent = &(clist->head);
	for (int i = 0; i < pos; i++)
	{
		pCurrent = pCurrent->next;
	}

	//���浱ǰ������һ�����
	CircleLinkNode* pNext = pCurrent->next;
	pCurrent->next = pNext->next;

	clist->size--;
}
//����ֵɾ��
void RemoveByValue_CircleLinkList(CircleLinkList* clist, CircleLinkNode* data, COMPARENODE compare)
{
	if (clist == NULL)
	{
		return;
	}
	if (data == NULL)
	{
		return;
	}

	//�����ѭ������
	CircleLinkNode* pPrev = &(clist->head);
	CircleLinkNode* pCurrent = pPrev->next;
	int i = 0;
	for (i = 0; i < clist->size; i++)
	{
		if (compare(pCurrent, data) == CIRCLELINKLIST_TRUE)
		{
			pPrev->next = pCurrent->next;
			break;
		}
		pPrev = pCurrent;
		pCurrent =pPrev->next;
	}

	clist->size--;
}
//���������
int Size_CircleLinkList(CircleLinkList* clist)
{
	return clist->size;
}

//�ж��Ƿ�Ϊ��
int IsEmpty_CiecleLinkList(CircleLinkList* clist)
{
	if (clist->size == 0)
	{
		return CIRCLELINKLIST_TRUE;
	}
	return CIRCLELINKLIST_FALST;
}
//����
int Find_CircleLinkList(CircleLinkList* clist, CircleLinkNode* data, COMPARENODE compare)
{
	if (clist == NULL)
	{
		return -1;
	}
	if (data == NULL)
	{
		return -1;
	}

	//����ָ�����
	CircleLinkNode* pCurrent = clist->head.next;
	int flag = -1;
	for (int i = 0; i < clist->size; i++)
	{
		if (compare(pCurrent, data) == CIRCLELINKLIST_TRUE)
		{
			flag = i;
			break;
		}
		pCurrent = pCurrent->next;
	}

	return flag;
}
//��ӡ���
void Print_CircleLinkList(CircleLinkList* clist, PRINTNODE print)
{
	if (clist == NULL)
	{
		return;
	}

	//����ָ�����
	CircleLinkNode* pCurrent = clist->head.next;
	for (int i = 0; i < clist->size ; i++)
	{
		// ������ָ��ͷ�ڵ�
		if (pCurrent == &(clist->head))
		{
			pCurrent = pCurrent->next;

		}
		print(pCurrent);
		pCurrent = pCurrent->next;
	}
	printf("-------------------\n");

}
//�ͷ��ڴ���
void FreeSpace_CircleLinkList(CircleLinkList* clist)
{
	if (clist == NULL)
	{
		return;
	}

	free(clist);
}

