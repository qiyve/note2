#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>


////A����
//int main()
//{
//	char szHandle[8] = { 0 };
//	char szBuffer[256] = { 0 };
//
//	//��ȫ����
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
//	//����һ�����Ա��̳е��ں˶��󣬴˴��Ǹ�����
//	STARTUPINFOA ie_si = { 0 };
//	PROCESS_INFORMATION ie_pi;
//	ie_si.cb = sizeof(ie_si);
//
//	CHAR szCmdline[] = "c://program files//internet explorer//iexplore.exe";
//	CreateProcessA(
//		NULL,
//		szCmdline,
//		&ie_sa_p,	//���̾���Ƿ�ɼ̳�
//		&ie_sa_t,	//�߳̾���Ƿ�ɼ̳�
//		TRUE,		//�Ƿ�ɼ̳и����̵ľ����
//		CREATE_NEW_CONSOLE, //CREATE_NEW_CONSOLE ����̨�����ӽ��̺͸����̶����Լ��Ŀ���̨����
//		NULL,
//		NULL,
//		&ie_si, &ie_pi
//	);
//
//	//��֯�����в���
//	sprintf(szHandle, "%x %x", ie_pi.hProcess, ie_pi.hThread);
//	sprintf(szBuffer, "D:/SSS.exe %s", szHandle);
//
//	//���崴��������Ҫ�Ľṹ��
//	STARTUPINFOA si = { 0 };
//	PROCESS_INFORMATION pi;
//	si.cb = sizeof(si);
//
//	//�����ӽ���
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
////B����
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
//	printf("��ȡIE���̡����߳̾��\n");
//	Sleep(2000);
//	//�������߳�                        
//	printf("�������߳�\n");
//	::SuspendThread((HANDLE)dwThreadHandle);
//	Sleep(5000);
//
//	//�ָ����߳�                        
//	::ResumeThread((HANDLE)dwThreadHandle);
//	printf("�ָ����߳�\n");
//	Sleep(5000);
//
//	//�ر�ID����                        
//	::TerminateProcess((HANDLE)dwProcessHandle, 1);
//	::WaitForSingleObject((HANDLE)dwProcessHandle, INFINITE);
//
//	printf("ID�����Ѿ��ر�.....\n");
//	return 0;
//}



//�Թ���ķ�ʽ�������̣���ȡ���̵�ImageBase��AddressOfEntryPoint
int main(int argc, char* argv[])
{

	TCHAR szAppName[256] = TEXT("D:\\ipmsg.exe");
	STARTUPINFO si = { 0 }; //������������
	si.cb = sizeof(si);		//ֻ��Ҫ���ݽṹ��С����
	PROCESS_INFORMATION pi;	//��¼�����Ϣ��

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

	//��ȡ��ڵ�								
	DWORD dwEntryPoint = contx.Eax;

	//��ȡImageBase								
	char* baseAddress = (CHAR*)contx.Ebx + 8;

	memset(szAppName, 0, 256);

	ReadProcessMemory(pi.hProcess, baseAddress, szAppName, 4, NULL);


	//�ָ�������
	::ResumeThread(pi.hThread);

	return 0;
}
