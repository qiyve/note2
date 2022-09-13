#include<stdio.h>
#include<Windows.h>
#include<tchar.h>

// 远程线程注入 步骤
//1. 获取进程句柄	2.计算dll名字	3.给目标进程申请空间
//4. 拷贝dll进去	5.获取模块地址	6.获取函数地址
//7. 创建远程线程	8.关闭句柄

VOID LoadDll(DWORD Did, char* PathName)
{
	//1、获取进程句柄 
	//打开本地进程对象  参数：指定所得句柄具有的访问权限、 是否可被继承、 指定要打开的进程ID
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, Did);
 

	//2、计算Dll名字长度  strlen 返回的字符串长度不包括 \0 
	DWORD dwLength = strlen(PathName) + 1;
 

	//3、给目标进程申请空间
	//	参数：1.申请内存所在的进程句柄 、2.保留页面的内存地址(一般用NULL)、3.预分配内存大小
	//		  4.分配内存空间的类型 、 5.内存访问权限 PAGE_READWRITE 可读可写
	LPSTR FileRemote = (LPSTR)VirtualAllocEx(hProcess, NULL, dwLength, MEM_COMMIT, PAGE_READWRITE);

 
	//4、拷贝DLL进去  WriteProcessMemory将数据写入指定进程中的内存区域
	//	参数：目标进程句柄、目标进程内存空间首地址、需要写入数据的内存空间地址、
	//	需要写入数据字节数、实际写入的字节数，设置为NULL
	WriteProcessMemory(hProcess, (LPVOID)FileRemote, (LPVOID)PathName, dwLength, NULL);


	//5、获取模块地址 
	//GetModuleHandleA 检索指定模块的模块句柄。该模块必须已由调用进程加载。
	HMODULE hkernel = GetModuleHandleA("Kernel32.dll");

	//6、获取函数地址
	//从指定的动态链接库 （DLL） 中检索导出的函数（也称为过程）或变量的地址。 
	DWORD loadAddr = (DWORD)GetProcAddress(hkernel, "LoadLibraryA");
	//DWORD loadAddr = (DWORD)GetProcAddress(hkernel, "LoadLibraryA");

	////7、创建远程线程 加载DLl
	DWORD threadID;
	//创建在另一个进程的虚拟地址空间中运行的线程
	//主要的三个参数 第一个：远程进程句柄、 第四个: 线程入口函数的起始地址、 第五个：传递给线程函数的参数
	HANDLE rThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)loadAddr, (LPVOID)FileRemote, 0, &threadID);

	//关闭句柄
	CloseHandle(rThread);

}

int _tmain(int argc, TCHAR* argv[])
{
	char DllBuf[] = "D:\\Cyuyan\\Dll1\\Debug\\Dll1.dll";

	LoadDll(21736, DllBuf);

	getchar();
	return 0;

}

//void LoadDll(DWORD Did, char* pathname) {
//
//
//
//
//
//	//6.获取函数地址
//	DWORD loadaddr = (DWORD)GetProcAddress(hkernel, "LoadLibraryA");
//	//7.创建远程线程 加载dll 
//
//	DWORD threadID;
//	HANDLE t = CreateRemoteThread(hprocess, NULL, 0, (LPTHREAD_START_ROUTINE)loadaddr, (LPVOID)FileRemote, 0, &threadID);
//	//8.关闭句柄
//	CloseHandle(t);
//
//}
