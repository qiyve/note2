#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>


int main01()
{
	//�����ַ�����
	char arr[5] = { 'h','e','l','l','o' };
	//�ַ�
	//char ch = 'a';
	//�ַ��� �ַ���������־Ϊ\0 ����0��ͬ��\0  ���ǲ���ͬ��0��
	//char* arr = "hello";
	//char arr[] = "hello";
	//char arr[] = { 'h','e','l','l','o','\0' };

	printf("%s", arr); //��ӡ�ַ���

	//printf("%d\n",sizeof(arr));  //sizeof (��������)
	
	//for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
	//{
	//	printf("%c", arr[i]);
	//}

	system("pause");
	return 0;
}

int main02()
{
	//�����ַ�����洢�ַ���
	char ch[10];

	//ע�⣺%s ���տո�ǰ������
	scanf("%s", ch);

	printf("%s", ch);

	system("pause");
	return 0;
}
int main()
{
	//�ַ���ƴ��
	char ch1[] = "hello";
	char ch2[] = "world";
	char ch3[20];

	int i = 0; //�±�
	int j = 0;

	while (ch1[i]!='\0')
	{
		ch3[i] = ch1[i];
		i++;
	}
	while (ch2[j]!='\0')
	{
		ch3[i + j] = ch2[j];
		j++;
	}

	ch3[i + j] = '\0';

	printf("%s", ch3);

	system("pause");
	return 0;
}