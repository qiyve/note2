#include <stdio.h>

void my_strcpy01(char* dest, char* ch)
{
	int i = 0;
	//while (ch[i] != '\0');
	//while (ch[i] != 0);
	while (ch[i])
	{

		dest[i] = ch[i];
		i++;
	}
	dest[i] = 0;// \0
}

void my_strcpy02(char* dest, char* ch)
{
	int i = 0;
	while (*(ch+i))
	{
		*(dest + i) = *(ch + i);
		i++;
	}
	*(dest + i) = 0; // \0
}

void my_strcpy03(char* dest, char* ch)
{
	while (*ch)
	{
		*dest = *ch;
		dest++;//ָ��+1 �൱��ָ���������һ��Ԫ�� �ڴ��ַ�仯��sizeof��char��
		ch++;
	}
	*dest = 0;
}

void my_strcpy(char* dest, char* ch)
{
	while (*dest++ = *ch++);
	// *dest  *ch 
	// *dest = *ch 
	//  dest++ ch++
	
}

int main01()
{
	//�ַ�������
	char ch[] = "hello world";
	char dest[100];
	
	my_strcpy(dest, ch);
	printf("%s\n", dest);

	system("pause");
	return 0;
}

int main02()
{

	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	//char* p ;
	int* p ;

	//arr/[-1] �����±�Խ��

	p = &arr[3];
	printf("%p\n", p);
	//p--;//ָ��ļ��������ָ��������й�
	//p--;
	//p--;

	//�ڴ��ַ���12 / sieof(int) =ƫ����
	//int step = p - arr;

	//printf("%d\n", step);

	//ָ���������ʱ�����±��Ǹ���
	printf("%d\n", p[-2]); //*(p-2)

	//printf("%p\n", p);
	//printf("%p\n", arr);


	system("pause");
	return 0;
}

int main()
{
	//ָ������������
	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	int* p = arr;
	p = &arr[3];

	//Ұָ��
	//p = p + arr; ��
	//p = p * arr;
	//p = p * 4;
	//p = p / arr;
	//p = p % 4;

	if (p > arr)
	{
		printf("��\n");
	}


	system("pause");
	return 0;
}