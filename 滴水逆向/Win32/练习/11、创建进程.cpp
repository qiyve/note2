#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>


//通过程序名创建进程
//VOID TestCreateProcessByAPPName()
//{
//	STARTUPINFO si = { 0 };
//	PROCESS_INFORMATION pi;
//
//	si.cb = sizeof(si);
//	TCHAR szApplicationName[] = TEXT("c://program files//internet explorer//iexplore.exe");
//
//	BOOL res = CreateProcess(
//		szApplicationName,  //CreateProcess的第一个参数用来接收需要运行的程序名
//		NULL,
//		NULL,
//		NULL,
//		FALSE,
//		CREATE_NEW_CONSOLE,
//		NULL,
//		NULL, 
//		&si,  // STARTUPINFO 结构，用来设定进程的属性
//		&pi); // 是一个out参数，传入PROCESS_INFORMATION结构，用来保存进程创建后的进程 句柄、进程ID。主线程句柄以及主线程ID	
//
//}


//通过命令行创建进程
//将命令行中的命令作为一个字符串传入CreateProcess的第二个参数；
//VOID TestCreateProcessByCmdline()
//{
//	STARTUPINFO si = { 0 };
//	PROCESS_INFORMATION pi;
//
//	si.cb = sizeof(si);
//	        
//	TCHAR szCmdline[] = TEXT("c://program files//internet explorer//iexplore.exe http://www.4399.com"); //程序名和参数之间加空格    
//
//	BOOL res = CreateProcess(
//		NULL,
//		szCmdline,
//		NULL,
//		NULL,
//		FALSE,
//		CREATE_NEW_CONSOLE,
//		NULL,
//		NULL, &si, &pi);
//}

//命令行和程序名组合使用
//VOID TestCreateProcess()
//{
//    STARTUPINFO si = { 0 };
//    PROCESS_INFORMATION pi;
//    si.cb = sizeof(si);
//    TCHAR szCmdline[] = TEXT(" http://www.4399.com");
//
//    BOOL res = CreateProcess(
//        TEXT("c://program files//internet explorer//iexplore.exe"),       //打开ie      
//        szCmdline,         //通过命令行传入ie用到的网址        
//        NULL,
//        NULL,
//        FALSE,
//        CREATE_NEW_CONSOLE,
//        NULL,
//        NULL, &si, &pi);
//}

int main01()
{
	//TestCreateProcessByAPPName(); 通过 程序名称创建进程

	//TestCreateProcessByCmdline(); //通过 命令行创建进程

    //TestCreateProcess();

	return 0;
}


int main(int argc, char* argv[])
{
	char szBuffer[256] = { 0 };
	char szHandle[8] = { 0 };

	//若要创建能继承的句柄，父进程必须指定一个SECURITY_ATTRIBUTES结构并对它进行初始化
	//三个成员的意义： 大小、默认安全属性、是否可以继承
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	//创建一个可以被继承的内核对象
	HANDLE g_hEnvent = CreateEvent(&sa, TRUE, FALSE, NULL);

	//组织命令行参数
	sprintf(szHandle, "%x", g_hEnvent);
	sprintf(szBuffer, "D://XXXXXX.exe %s", szHandle);

	//定义创建进程需要用的结构体
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);

	// 创建子进程
	BOOL res = CreateProcess(
		NULL,
		(LPWSTR)szBuffer,
		NULL,
		NULL,
		TRUE,           //TRUE的时候，说明子进程可以继承父进程的句柄表
		CREATE_NEW_CONSOLE,
		NULL,
		NULL, &si, &pi);

	//设置事件为已通知
	SetEvent(g_hEnvent);
	//关闭句柄 内核对象并不会被销毁
	CloseHandle(g_hEnvent);
						
	return 0;

}
