#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>

void my_strcat(char* dest, char* src)
{
	while (*dest)dest++; //��ȡdest�ַ�����\0��λ��
	while (*dest++ = *src++);
}

void my_strncat(char* dest, char* src, size_t n)
{
	while (*dest)dest++;
	while ((*dest++ = *src++) && --n);
}

int main()
{
	char dest[100] = "hello";
	char src[] = "wrold";

	//�ַ���׷��
	//strcat(dest, src);
	//my_strcat(dest, src);

	//����׷��
	//strncat(dest, src, 3);
	my_strncat(dest, src, 3);
	printf("%s\n", dest);

	system("pause");
	return 0;
}