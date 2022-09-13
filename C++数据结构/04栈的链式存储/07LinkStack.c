#include"07LinkStack.h"


//��ʼ������
LinkStack* Init_LinkStack()
{
	LinkStack* stack = (LinkStack*)malloc(sizeof(LinkStack));
	stack->size = 0;
	stack->head.dext = NULL;
	return stack;
}
//��ջ
void Push_LinkStack(LinkStack* stack, LinkNode* data)
{
	if (stack == NULL)
	{
		return;
	}
	if (data == NULL)
	{
		return;
	}

	//��ջ
	data->dext = stack->head.dext;
	stack->head.dext = data;
	stack->size++;

}
//��ջ
void Pop_LinkStack(LinkStack* stack)
{
	if (stack == NULL)
	{
		return ;
	}
	if (stack->size == 0)
	{
		return;
	}
	
	//��һ����Ч���
	LinkNode* pNext = stack->head.dext;
	stack->head.dext = pNext->dext;

	stack->size--;
}
//����ջ��Ԫ��
LinkNode* Top_LinkStack(LinkStack* stack)
{
	if (stack == NULL)
	{
		return -1;
	}
	if (stack->size == 0)
	{
		return -1;
	}
	return stack->head.dext;
}
//����Ԫ�ظ���
int Size_LinkStack(LinkStack* stack)
{
	if (stack == NULL)
	{
		return -1;
	}

	return stack->size;
}
//���ջ
void Clera_LinkStack(LinkStack* stack)
{
	if (stack == NULL)
	{
		return;
	}
	stack->head.dext = NULL;
	stack->size = 0;
}
//����ջ
void FreeSpace_LinkStack(LinkStack* stack)
{
	if (stack == NULL)
	{
		return;
	}
	free(stack);

}
