#include <stdio.h>

int my_strlen01(char* ch)
{
	//�����ַ�����Ч����
	int i = 0;
	//while (ch[i] != '\0')
	//{
	//	i++;
	//}
	while (ch[i])i++;

	return i;
}
int my_strlen(const char* ch) //ֻ�������޸�
{
	char* temp = ch; //����ָ��
	//while (*temp != '\0')temp++;
	while (*temp)temp++;
	return temp - ch; 
}

int main()
{
	char ch[] = "hello wrold";
	//printf("%s\n", ch); ch���׵�ַ %s���α�����\0
	int len= my_strlen(ch);

	printf("%d\n", len);


	system("pause");
	return 0;
}