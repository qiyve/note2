#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"LinkStack.h"

//�ж��Ƿ�������
int IsNumber(char c)
{
	return c >= '0' && c <= '9';
}

//�ж��ǲ���������
int IsLeft(char c)
{
	return c == '(';
}

//�ж��ǲ���������
int IsRight(char c)
{
	return c == ')';
}

//�ж��ǲ��������
int IsOperator(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}

typedef struct MYCHAR
{
	LinkNode node;
	char* p;

}MyChar;


//���ֲ���
void NumberOperate(char* p)
{
	printf("%c", *p);
}

//����MyChar
MyChar* CreateMyChar(char* p)
{
	MyChar* mychar = (MyChar*)malloc(sizeof(MyChar));
	mychar->p = p;
	return mychar;
}

//�����Ų���
void LeftOperate(LinkStack* stack, char* p)
{
	Push_LinkStack(stack, (LinkNode*)CreateMyChar(p));
}

//�����Ų���
void RightOperate(LinkStack* stack)
{
	//���ж�ջ����û��Ԫ��
	while (Size_LinkStack(stack) > 0)
	{
		MyChar* mychar = (MyChar*)Top_LinkStack(stack);

		//���ƥ�䵽�����ŵ���
		if (IsLeft(*(mychar->p)))
		{
			Pop_LinkStack(stack);
			break;
		}

		//���
		printf("%c", *(mychar->p));
		//����
		Pop_LinkStack(stack);
		//�ͷ��ڴ�
		//free(mychar);
	}
}


//��������������ȼ�
int GetPriority(char c)
{
	if (c == '*' || c == '/')
	{
		return 2;
	}
	if (c == '+' || c == '-')
	{
		return 1;
	}
	return 0;
}

//������ŵĲ���
void OperatorOperate(LinkStack* stack, char* p)
{
	//��ȡ��ջ������ // �޷���ȡ�ڴ治��NULL
	MyChar* mychar = (MyChar*)Top_LinkStack(stack);
	if (mychar == NULL)
	{
		Push_LinkStack(stack, (LinkNode*)CreateMyChar(p));
		return;
    }

	//���ջ�����ȼ����ڵ�ǰ�ַ������ȼ� ֱ����ջ
	if (GetPriority(*(mychar->p)) < GetPriority(*p))
	{
		Push_LinkStack(stack, (LinkNode*)CreateMyChar(p));
		return;
	}

	//���ջ���������ȼ�����
	else 
	{
		while (Size_LinkStack(stack) > 0 )
		{
			MyChar* mychar2 = (MyChar*)Top_LinkStack(stack);
			//������ȼ��� ��ǰ������ջ
			if (GetPriority(*(mychar2->p)) < GetPriority(*p))
			{
				Push_LinkStack(stack, (LinkNode*)CreateMyChar(p));
				return;
			}

			//���
			printf("%c", *(mychar2->p));
			//����
			Pop_LinkStack(stack);
			//�ͷ�
			free(mychar2);
		}
	}
	
}



int main()
{
	
	char* str = "8+(3-1)*5";
	char* p = str;

	//����ջ
	LinkStack* stack = Init_LinkStack();


	while (*p != '\0')
	{
		//���������
		if (IsNumber(*p))
		{
			NumberOperate(p);
		}

		//����������� ֱ�ӽ�ջ
		if (IsLeft(*p))
		{
			LeftOperate(stack, p);
		}

		//����������� ��ջ��Ԫ�ص��� ֱ�������Ž���
		if (IsRight(*p))
		{
			RightOperate(stack);
		}

		//������������
		if (IsOperator(*p))
		{
			OperatorOperate(stack,p);
		}
		p++;
	}

	while (Size_LinkStack(stack) > 0)
	{
		MyChar* mychar = (MyChar*)Top_LinkStack(stack);
		printf("%c", *(mychar->p));
		Pop_LinkStack(stack);
		free(mychar);
	}

	system("pause");
	return 0;
}