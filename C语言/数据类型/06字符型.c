#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>	


int main01(void)
{
	//�ַ��ͱ���

	char ch = 'a';

	//��ӡ�ַ��ͱ���
	printf("%c\n", ch);
	//��ӡch��Ӧ��ʮ����
	printf("%d\n", ch);

	// unsigned int len = sizeof(ch)
	printf("�ַ��ʹ�С��%d\n", sizeof(ch));

	return 0;
}

int main()
{
	/*char ch1 = 'a';
	char ch2 = 'A';
	printf("%d\n",ch1 - ch2);*/

	//Сд��ĸת��д��ĸ
	char ch;
	scanf("%c", &ch);

	printf("%c\n", ch-32);


	return 0;
}
