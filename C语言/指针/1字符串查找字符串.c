#include <stdio.h>

char* my_strstr(char* src, char* dest)
{
	char* fsrc = src;//���ڱ���ѭ����ָ��
	char* rsrc = src; //��¼ÿ����ͬ���׵�ַ

	char* tdest = dest; //���ҵ��ַ����׵�ַ

	while (*fsrc)
	{
		rsrc = fsrc;
		while (*fsrc == *tdest && *fsrc != '\0')
		{
			fsrc++;
			tdest++;
		}

		if (*tdest == '\0')
		{
			return rsrc;
		}
		//�ع�
		fsrc = rsrc;
		tdest = dest;

		fsrc++;
	}
	return NULL;
}
int main()
{
	char src[] = "helloo world";
	char dest[] = "lloo";

	char* p = my_strstr(src,dest);

	printf("%s\n", p);
	
	system("pause");
	return 0;
}

