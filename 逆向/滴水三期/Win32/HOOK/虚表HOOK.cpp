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
	printf("hook成功\n");
}

int main()
{
	Base* base = new Base();	//创建对象
	//获取虚表起始地址      将base 强转成 DWORD* 在取地址  最后强转赋值
	DWORD* pb = (DWORD*)*(DWORD*)base;
	DWORD n;	//接收指定页区域中第一页的上一个访问保护值
	VirtualProtect(pb, 4, PAGE_EXECUTE_READWRITE, &n);
	*pb = (DWORD)Myfunc;//将自己函数地址赋值给它
	base->func();
	return 0;
}
