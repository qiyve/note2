#include<stdio.h>

int main01(void)
{
	//�������� ��ʶ�� = ֵ
	//�޷���  unsigned  �з��� signed
	signed int a = -10;

	//unsigned int a = 10;  
	//%u ռλ�� ��ʾ���һ���޷����޷���ʮ������������
	//printf("%u\n", a);

	printf("%d\n", a);
	return 0;
}

int main()
{
	//����
    //������0-1  �˽���0-7  ʮ������0-9 10-15��a-f A-F)

	//int a = 10;
	//printf("%d\n", a);
	////ռλ�� %x ���һ��ʮ����������
	//printf("%x\n", a);
	//printf("%X\n", a);
	////ռλ�� %o ���һ���˽�������
	//printf("%o\n", a);

	//����˽������� ��0��ͷ
	int a = 0123;
	//����ʮ���������� ��0x��ͷ
	int b = 0x123;
	//�ڼ������������ʱ ������ֱ�Ӷ��������
	printf("%d\n", a);
	printf("%o\n", a);
	printf("%x\n", a);

	printf("%d\n", b);
	printf("%o\n", b);
	printf("%x\n", b);


	return 0;

}