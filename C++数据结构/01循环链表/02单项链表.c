#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include"02LinKist.h"

//�Զ�����������
typedef struct PERSON
{
	char name[64];
	int age;
	int score;
}Preson;

//��ӡ����
void MyPrint(void* data)
{
	Preson* p = (Preson*)data;
	printf("Name:%s Age:%d Scoer:%d\n", p->name, p->age, p->score);
}

int main()
{
	//��������
	LinkList* list = Init_LinkList();

	//��������
	Preson p1 = { "aaa",16,100 };
	Preson p2 = { "bbb",17,70 };
	Preson p3 = { "ccc",12,82 };
	Preson p4 = { "ddd",19,65 };
	Preson p5 = { "fff",13,60 };

   //���ݲ�������
	Insert_LinkList(list, 0, &p1);
	Insert_LinkList(list, 0, &p2);
	Insert_LinkList(list, 0, &p3);
	Insert_LinkList(list, 0, &p4);
	Insert_LinkList(list, 0, &p5);

	//��ӡ
	Preint_LinkList(list, MyPrint);

	//ɾ�� 3
	RemoveByPos_LinkList(list, 3);
	//��ӡ
	printf("--------------\n");
	Preint_LinkList(list, MyPrint);

	//���ص�һ�����
	Preson*ret = (Preson*)Front_LinkList(list);
	printf("------��һ�����ֵΪ--------\n");
	printf("Name:%s Age:%d Scoer:%d\n", ret->name, ret->age, ret->score);

	//����
	int fd = Find_LinkList(list, &p2);
	printf("------���ҳɹ�--------\n");
	printf("%d\n", fd);

	//��������
	FreeSpace_LinkList(list);


	return 0;
}