#include <stdio.h>

void swap01(int a, int b)
{
	int temp = a;
	a = b;
	b = temp;
}
//ָ����Ϊ��������
void swap02(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


int main()
{
	int a = 10;
	int b = 20;

	//ֵ���� �ββ�Ӱ��ʵ�ε�ֵ
	/*swap01(a, b);
	printf("%d\n", a);
	printf("%d\n", b);*/

	//��ַ���� �βλ�Ӱ��ʵ��
	swap02(&a, &b);
	printf("%d\n", a);
	printf("%d\n", b);

	system("pause");
	return 0;
}
