#include <iostream>
#include <Windows.h>

class Base
{
public:
	virtual void func()
	{
		printf("func\n");
	}
};

void Myfunc()
{
	printf("hook�ɹ�\n");
}

int main()
{
	Base* base = new Base();	//��������
	//��ȡ�����ʼ��ַ      ��base ǿת�� DWORD* ��ȡ��ַ  ���ǿת��ֵ
	DWORD* pb = (DWORD*)*(DWORD*)base;
	DWORD n;	//����ָ��ҳ�����е�һҳ����һ�����ʱ���ֵ
	VirtualProtect(pb, 4, PAGE_EXECUTE_READWRITE, &n);
	*pb = (DWORD)Myfunc;//���Լ�������ַ��ֵ����
	base->func();
	return 0;
}
