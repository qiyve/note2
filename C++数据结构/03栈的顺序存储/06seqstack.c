#include"06seqstack.h"


//��ʼ��ջ
SeqStack* Init_SeqStack()
{
	SeqStack* stack = (SeqStack*)malloc(sizeof(SeqStack));
	for (int i = 0; i < MAX_SIZE; i++)
	{
		stack->data[i] = NULL;
	}
	stack->size = 0;
	return stack;
}
//��ջ
void Push_SeqStack(SeqStack* stack, void* data)
{
	if (stack->size == MAX_SIZE)
	{
		return;
	}

	if (stack == NULL)
	{
		return;
	}
	if (data == NULL)
	{
		return;
	}

	//��ջ
	stack->data[stack->size] = data;
	stack->size++;

}
//����ջ��Ԫ��
void* Top_SeqStack(SeqStack* stack)
{
	if (stack == NULL)
	{
		return NULL;
	}
	if (stack->size == 0)
	{
		return NULL;
	}

	return stack->data[stack->size - 1];
}
//��ջ
void Pop_SeqStack(SeqStack* stack)
{
	if (stack == NULL)
	{
		return;
	}
	if (stack->size == 0)
	{
		return;
	}

	//��ջ
	stack->data[stack->size - 1] = NULL;
	stack->size--;
}
//�ж��Ƿ�Ϊ��
int IsEmpty(SeqStack* stack)
{
	if (stack == NULL)
	{
		return -1;
	}
	if (stack->size == 0)
	{
		return SEQSTACK_TRUE;
	}

	return SEQSTACK_FLAST;
}
//����ջ�е�Ԫ�ظ���
int Size_SeqStack(SeqStack* stack)
{
	return stack->size;
}
//�ͷ�
void FreeSpace(SeqStack* stack)
{
	if (stack != NULL)
	{
		free(stack);
	}
}
