#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>


int main01()
{
	char ch[100];

	//ͨ�����̻�ȡ�ַ���
	//gets�����ַ������Դ��ո�
	gets(ch);
	//ͨ��������ʽ ��ȡ���ո��ַ���
	//scanf("%[^\n]", ch); 

	printf("%s\n", ch);

	system("pause");
	return 0;
}

int main02()
{
   //fgets����
	char ch[10];
	//"hello \n\0" 
	//fgets ���Խ��տո�
	//fgets��ȡ�ַ�������Ԫ�ظ�����\n  ���ڵ��� û��\n
	fgets(ch,sizeof(ch),stdin); //stdin ϵͳ�ṩ��ָ��

	printf("%s\n", ch);

	system("pause");
	return 0;
}

//��� puts()
int main04()
{
	char ch[] = "hello world";

	//puts �Դ�����
	//puts(ch);
	//puts ���� \0����
	puts("hello \0 world");
	//puts("");  ����

	system("pause");
	return 0;
}

//��� fputs
int main()
{
	char ch[] = "hello world";

	//int fputs(const* str, FILE * stream) stream �ļ�ָ�� �̶�дstdout
	fputs(ch, stdout);

	system("pause");
	return 0;
}