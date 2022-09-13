#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"LinkStack.h"

typedef struct MYCHAR {

	LinkNode node;
	char* pAddres;
	int index;
}MyChar;

int IsLeft(char c)
{
	return c == '(';
}
int IsRight(char c)
{
	return c == ')';
}

MyChar* CreatMyChar(char* p,int index)
{
	MyChar* mychar = (MyChar*)malloc(sizeof(MyChar));
	mychar->pAddres = p;
	mychar->index = index;

	return mychar;
}

void ShowError(char* str, int pos)
{
	printf("%s\n", str);
	for (int i = 0; i < pos; i++)
	{
		printf(" ");
	}
	printf("A"); //��ͷ
}

int main()
{
	char* str = "1+2+6(dsf)dfsf)lp(sdfs)";

	//����ջ����
	LinkStack* stack = Init_LinkStack();

	char* p = str;
	int index = 0;
	while (*p != '\0')
	{
		//��������� ֱ�ӽ�ջ
		if (IsLeft(*p))
		{
			Push_LinkStack(stack,(LinkNode*) CreatMyChar(p,index));
		}
		//����������� ��ջ������Ԫ��  �ж��ǲ���������
		if (IsRight(*p))
		{
			if (Size_LinkStack(stack) > 0)
			{
				MyChar* mychar = (MyChar*)Top_LinkStack(stack);
				if (IsLeft(*(mychar->pAddres)))
				{
					Pop_LinkStack(stack);
				}
				free(mychar);
			}
			else
			{
				printf("������û��ƥ���������\n");
				ShowError(str, index);
				break;
			}
		}
		p++;
		index++;
	}
	//��ӡ
	while (Size_LinkStack(stack) > 0)
	{
		MyChar* mychar = (MyChar*)Top_LinkStack(stack);
		printf("������û��ƥ��������ţ�\n");
		ShowError(str, mychar->index);
		Pop_LinkStack(stack);

		free(stack);
	}
	printf("\n");

	system("pause");
	return 0;
}