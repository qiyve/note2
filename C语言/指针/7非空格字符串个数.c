#include <stdio.h>

int getstrcount01(char* ch)
{
	int i = 0;
	int count = 0;
	while (ch[i])
	{
		if (ch[i] != ' ')
		{
			count++;
		}
		i++;
	}
	return count;
}

int getstrcount(char* ch)
{
	int count = 0;
	while (*ch)
	{
		if (*ch != ' ')count++;
		ch++;
	}
	return count;
}

int main01()
{
	char ch[] = " h e  ll o  wor l d";

	int len = getstrcount(ch);

	printf("%d\n", len);

	return 0;
}

int main()
{
	//ͳ���ַ������ִ���
	char ch[] = "hello world n ich oush ac ho un iz adi ";

	//�洢�ַ������ִ���
	int arr[26] = { 0 };

	for (int i = 0; i < strlen(ch); i++)
	{
		//ch[i] ch�ж�Ӧλ���ַ���ֵ - a��Ӧ����ֵ �ó���Ӧ��ֵ���ַ� ÿ����һ�ξ�++
		arr[ch[i] - 'a']++;
	}

	for (int i = 0; i < 26; i++)
	{
		if (arr[i]) //arr[i]!= 0
		{
			printf("��ĸ��%c ���ִ���%d\n", i + 'a', arr[i]);
		}
	}

	return 0;
}
