#include <stdio.h>



int main()
{
	int a = 10;
	//int* p = &a;
	//����ָ����Խ����������ͱ������ڴ��ַ
	void* p = &a;
	//��ͨ������ָ���޸ı�������ֵʱ ��Ҫ�ҵ���Ӧ��ָ������
	*(int*)p = 100;
	printf("%d\n", a);
	printf("%d\n", *(int*)p);

	printf("%p\n", p);
	printf("����ָ����ռ�ֽڣ�%d\n", sizeof(void*));
	//printf("void��ռ�ֽڣ�%d\n", sizeof(void));


	system("pause");
	return 0;
}