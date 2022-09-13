#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>


////A进程
//int main()
//{
//	char szHandle[8] = { 0 };
//	char szBuffer[256] = { 0 };
//
//	//安全属性
//	SECURITY_ATTRIBUTES ie_sa_p;
//	ie_sa_p.nLength = sizeof(ie_sa_p);
//	ie_sa_p.lpSecurityDescriptor = NULL;
//	ie_sa_p.bInheritHandle = TRUE;
//
//	SECURITY_ATTRIBUTES ie_sa_t;
//	ie_sa_t.nLength = sizeof(ie_sa_t);
//	ie_sa_t.lpSecurityDescriptor = NULL;
//	ie_sa_t.bInheritHandle = TRUE;
//
//	//创建一个可以被继承的内核对象，此处是个进程
//	STARTUPINFOA ie_si = { 0 };
//	PROCESS_INFORMATION ie_pi;
//	ie_si.cb = sizeof(ie_si);
//
//	CHAR szCmdline[] = "c://program files//internet explorer//iexplore.exe";
//	CreateProcessA(
//		NULL,
//		szCmdline,
//		&ie_sa_p,	//进程句柄是否可继承
//		&ie_sa_t,	//线程句柄是否可继承
//		TRUE,		//是否可继承父进程的句柄表
//		CREATE_NEW_CONSOLE, //CREATE_NEW_CONSOLE 控制台程序，子进程和父进程都有自己的控制台窗口
//		NULL,
//		NULL,
//		&ie_si, &ie_pi
//	);
//
//	//组织命令行参数
//	sprintf(szHandle, "%x %x", ie_pi.hProcess, ie_pi.hThread);
//	sprintf(szBuffer, "D:/SSS.exe %s", szHandle);
//
//	//定义创建进程需要的结构体
//	STARTUPINFOA si = { 0 };
//	PROCESS_INFORMATION pi;
//	si.cb = sizeof(si);
//
//	//创建子进程
//	BOOL res = CreateProcessA(
//		NULL,
//		szBuffer,
//		NULL,
//		NULL,
//		TRUE,
//		CREATE_NEW_CONSOLE,
//		NULL,
//		NULL, &si, &pi
//
//	);
//
//	return 0;
//}
//
//
//
//
////B进程
//int main(int argc, char* argv[]) {
//	DWORD dwProcessHandle = -1;
//	DWORD dwThreadHandle = -1;
//	char szBuffer[256] = { 0 };
//
//	memcpy(szBuffer, argv[1], 8);
//	sscanf(szBuffer, "%x", &dwProcessHandle);
//
//	memset(szBuffer, 0, 256);
//	memcpy(szBuffer, argv[2], 8);
//	sscanf(szBuffer, "%x", &dwThreadHandle);
//
//	printf("获取IE进程、主线程句柄\n");
//	Sleep(2000);
//	//挂起主线程                        
//	printf("挂起主线程\n");
//	::SuspendThread((HANDLE)dwThreadHandle);
//	Sleep(5000);
//
//	//恢复主线程                        
//	::ResumeThread((HANDLE)dwThreadHandle);
//	printf("恢复主线程\n");
//	Sleep(5000);
//
//	//关闭ID进程                        
//	::TerminateProcess((HANDLE)dwProcessHandle, 1);
//	::WaitForSingleObject((HANDLE)dwProcessHandle, INFINITE);
//
//	printf("ID进程已经关闭.....\n");
//	return 0;
//}



//以挂起的方式创建进程，获取进程的ImageBase和AddressOfEntryPoint
int main(int argc, char* argv[])
{

	TCHAR szAppName[256] = TEXT("D:\\ipmsg.exe");
	STARTUPINFO si = { 0 }; //程序启动设置
	si.cb = sizeof(si);		//只需要传递结构大小即可
	PROCESS_INFORMATION pi;	//记录句柄信息等

	::CreateProcess(
		NULL,
		szAppName,
		NULL,
		NULL,
		FALSE,
		CREATE_SUSPENDED,
		NULL,
		NULL,
		&si,
		&pi
	);

	CONTEXT contx;
	contx.ContextFlags = CONTEXT_FULL;


	GetThreadContext(pi.hThread, &contx);

	//获取入口点								
	DWORD dwEntryPoint = contx.Eax;

	//获取ImageBase								
	char* baseAddress = (CHAR*)contx.Ebx + 8;

	memset(szAppName, 0, 256);

	ReadProcessMemory(pi.hProcess, baseAddress, szAppName, 4, NULL);


	//恢复主进程
	::ResumeThread(pi.hThread);

	return 0;
}
