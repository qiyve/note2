#include<stdio.h>
#include<Windows.h>
#include<tchar.h>

// Զ���߳�ע�� ����
//1. ��ȡ���̾��	2.����dll����	3.��Ŀ���������ռ�
//4. ����dll��ȥ	5.��ȡģ���ַ	6.��ȡ������ַ
//7. ����Զ���߳�	8.�رվ��

VOID LoadDll(DWORD Did, char* PathName)
{
	//1����ȡ���̾�� 
	//�򿪱��ؽ��̶���  ������ָ�����þ�����еķ���Ȩ�ޡ� �Ƿ�ɱ��̳С� ָ��Ҫ�򿪵Ľ���ID
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, Did);
 

	//2������Dll���ֳ���  strlen ���ص��ַ������Ȳ����� \0 
	DWORD dwLength = strlen(PathName) + 1;
 

	//3����Ŀ���������ռ�
	//	������1.�����ڴ����ڵĽ��̾�� ��2.����ҳ����ڴ��ַ(һ����NULL)��3.Ԥ�����ڴ��С
	//		  4.�����ڴ�ռ������ �� 5.�ڴ����Ȩ�� PAGE_READWRITE �ɶ���д
	LPSTR FileRemote = (LPSTR)VirtualAllocEx(hProcess, NULL, dwLength, MEM_COMMIT, PAGE_READWRITE);

 
	//4������DLL��ȥ  WriteProcessMemory������д��ָ�������е��ڴ�����
	//	������Ŀ����̾����Ŀ������ڴ�ռ��׵�ַ����Ҫд�����ݵ��ڴ�ռ��ַ��
	//	��Ҫд�������ֽ�����ʵ��д����ֽ���������ΪNULL
	WriteProcessMemory(hProcess, (LPVOID)FileRemote, (LPVOID)PathName, dwLength, NULL);


	//5����ȡģ���ַ 
	//GetModuleHandleA ����ָ��ģ���ģ��������ģ��������ɵ��ý��̼��ء�
	HMODULE hkernel = GetModuleHandleA("Kernel32.dll");

	//6����ȡ������ַ
	//��ָ���Ķ�̬���ӿ� ��DLL�� �м��������ĺ�����Ҳ��Ϊ���̣�������ĵ�ַ�� 
	DWORD loadAddr = (DWORD)GetProcAddress(hkernel, "LoadLibraryA");
	//DWORD loadAddr = (DWORD)GetProcAddress(hkernel, "LoadLibraryA");

	////7������Զ���߳� ����DLl
	DWORD threadID;
	//��������һ�����̵������ַ�ռ������е��߳�
	//��Ҫ���������� ��һ����Զ�̽��̾���� ���ĸ�: �߳���ں�������ʼ��ַ�� ����������ݸ��̺߳����Ĳ���
	HANDLE rThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)loadAddr, (LPVOID)FileRemote, 0, &threadID);

	//�رվ��
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
//	//6.��ȡ������ַ
//	DWORD loadaddr = (DWORD)GetProcAddress(hkernel, "LoadLibraryA");
//	//7.����Զ���߳� ����dll 
//
//	DWORD threadID;
//	HANDLE t = CreateRemoteThread(hprocess, NULL, 0, (LPTHREAD_START_ROUTINE)loadaddr, (LPVOID)FileRemote, 0, &threadID);
//	//8.�رվ��
//	CloseHandle(t);
//
//}
