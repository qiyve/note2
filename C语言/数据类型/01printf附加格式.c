#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>	


int main01()
{
	
	int a = 10;
	int c = 123456;

	// Ĭ��Ϊ�Ҷ���  ����� ���� -
	printf("===%-5d===\n", a);
	// m(����һ������)   ������С���
	// 0����0          �������ǰ�油��0ֱ��մ��ָ���п�Ϊֹ�����Դ���ʹ�� -
	printf("===%05d===\n", a);
	printf("===%05d===\n", c);//�������ָ����� �������

	/*m.n(��������) mָ�����Ӧ����豸����ռ�ַ�����nָ���ȣ�˵�������ʵ������С��λ����
	 ����ֵ����˵��δָ��nʱ�������ľ���Ϊ n=6λ */

	float b = 3.14;
	printf("===%-7.2f===",b); //��������0����

	return 0;
}

int main()
{
	char ch = 'a';

	//printf("%c\n", ch);
	//����ַ�
	//putchar(ch);
	//putchar('B');
	//putchar(97);
	putchar('\n');


	return 0;
}