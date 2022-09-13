#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>


 //父进程 
int main(int argc, char* argv[])
{
	//若要创建能继承的句柄，父进程必须指定一个SECURITY_ATTRIBUTES结构并对它进行初始化							
	//三个成员的意义：大小、默认安全属性、是否可以继承							
	char szBuffer[256] = { 0 };
	char szHandle[8] = { 0 };
	//若要创建能继承的句柄，父进程必须指定一个SECURITY_ATTRIBUTES结构并对他进行初始化
	//三个成员的意义：大小、默认安全属性、是否可以继承
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	//创建一个可以被继承的内核对象
	HANDLE hEvent = CreateEvent(&sa, TRUE, FALSE, NULL);

	//组织命令行参数
	sprintf(szHandle, "%x", hEvent);
     
	// 路径拼接 命令参数时需要 用空格 隔开
	sprintf(szBuffer, "D:\\XXX.exe %zx", szHandle);   // %zx  z表示 size_t :32位 无符号4字节 ; 64位 无符号8字节

	//定义创建进程需要的结构体
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);

	//创建子进程
	BOOL res = CreateProcessA(
		NULL,				//应用程序名称
		szBuffer,			//命令行字符串
		NULL,				//线程安全属性
		NULL,				//进程安全属性
		TRUE,				// 是否继承父进程的属性
		CREATE_NEW_CONSOLE, // 创建标志
		NULL,				// 指向新的环境块的指针
		NULL,				// 指向当前目录名的指针
		&si,				// 传递给新进程的信息
		&pi					// 新进程返回的信息
		);
	
	//设置事件为已通知
	SetEvent(hEvent);

	//关闭句柄 内核对象并会不会被销毁
	CloseHandle(hEvent);

	return 0;
}

//子进程
int main(int argc, char* argv[]) {

	printf("%s\n", argv[0]);

	HANDLE hEvent;
	sscanf(argv[1], "%zx", &hEvent);
	printf("%zx\n", hEvent);

	printf("开始等待.....\n");
	//当事件变成已通知时                 
	WaitForSingleObject(hEvent, INFINITE);
	DWORD dwCode = GetLastError();
	printf("等到消息.....%x\n", dwCode);
	getchar();
	return 0;
}