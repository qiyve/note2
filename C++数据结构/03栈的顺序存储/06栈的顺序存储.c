#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"06seqstack.h"

typedef struct PERSON {

	char name[64];
	int  age;
}Person;

int main()
{
	//����ջ
	SeqStack* stack = Init_SeqStack();

	//��������
	Person p1 = { "aaa",10 };
	Person p2 = { "bbb",20 };
	Person p3 = { "ccc",30 };
	Person p4 = { "ddd",40 };
	Person p5 = { "eee",50 };

	//��ջ
	Push_SeqStack(stack, &p1);
	Push_SeqStack(stack, &p2);
	Push_SeqStack(stack, &p3);
	Push_SeqStack(stack, &p4);
	Push_SeqStack(stack, &p5);

	//���
	while (Size_SeqStack(stack)>0)
	{
		//����ջ��Ԫ��
		Person* person = (Person*)Top_SeqStack(stack);
		printf("Name:%s Age:%d\n", person->name, person->age);
		//����ջ��Ԫ��
		Pop_SeqStack(stack);
	}
	
	//�ͷ��ڴ�
	FreeSpace(stack);

	
	return 0;
}