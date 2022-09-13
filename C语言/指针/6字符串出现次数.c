#include <stdio.h>

char* my_strstr(char* str, char* dest)
{
	char* fstr = str;
	char* rstr = str;
	char* tdest = dest; //���ҵ��ַ����׵�ַ

	while (*fstr)
	{
		rstr = fstr;
		while (*fstr == *tdest && *fstr != '\0')
		{
			fstr++;
			tdest++;
		}

		if (*tdest == '\0')
		{
			return rstr;
		}

		fstr = rstr;
		tdest = dest;

		fstr++;
	}

	return NULL;
}


int main01()
{
	char* str = "lloabclloasdllozzxllo";

	char ch[] = "llo";
	char* p = my_strstr(str, ch);
	int count = 0;//��¼����

	while (p)
	{
		count++;

		p += strlen(ch);
		p = my_strstr(p, ch);
	}

	printf("llo���ַ����г��֣�%d\n",count );

	return 0;
}

int main()
{
	char* str = "lloabclloasdllozzxllo";

	char ch[] = "llo";
	char* p = my_strstr(str, ch);
	int count = 0;//��¼����

	do
	{
		if (p)
		{
			count++;
			p += strlen(ch);
			p = my_strstr(p, ch);
		}
	} while (p);

	printf("llo���ַ����г��֣�%d\n", count);

	return 0;
}