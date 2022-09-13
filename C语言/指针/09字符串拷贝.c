#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>

void my_strcpy(char* dest, const char* str)
{
	while (*dest++ = *str++);
}

void my_strncpy04(char* dest, char* str, size_t num)
{
	while ((*dest++ = *str++) && --num);
}

void my_strncpy01(char* dest, char* str, size_t n)
{
	for (int i = 0; i < n; i++)
	{
		dest[i] = str[i];
	}
}
void my_strncpy02(char* dest, char* str, size_t n)
{
	int i = 0;
	while (i < n)
	{
		*(dest + i) = *(str + i);
		i++;
	}
}
void my_strncpy(char* dest, char* str, size_t n)
{
	while (n--&&*str)
	{
		*dest = *str;

		dest++;
		str++;
	}
}

int main()
{
	char ch[] = "hello wrold";

	char str[100] = { 0 };

	//�ַ�������
	//���Ŀ����ָ���ڴ�ռ䲻���󣬿��ܻ���ɻ�������Ĵ������
	//strcpy(str, ch); //����1 ����Ŀ��  ����2 Դ�ַ��׵�ַ
	//my_strcpy(str, ch);
	
	//�ַ������޿��� 
	//strncpy(str, ch, 6);
	my_strncpy(str, ch, 6);

	printf("%s\n", str);

	return 0;
}