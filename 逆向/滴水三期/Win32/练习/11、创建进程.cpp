#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>


//ͨ����������������
//VOID TestCreateProcessByAPPName()
//{
//	STARTUPINFO si = { 0 };
//	PROCESS_INFORMATION pi;
//
//	si.cb = sizeof(si);
//	TCHAR szApplicationName[] = TEXT("c://program files//internet explorer//iexplore.exe");
//
//	BOOL res = CreateProcess(
//		szApplicationName,  //CreateProcess�ĵ�һ����������������Ҫ���еĳ�����
//		NULL,
//		NULL,
//		NULL,
//		FALSE,
//		CREATE_NEW_CONSOLE,
//		NULL,
//		NULL, 
//		&si,  // STARTUPINFO �ṹ�������趨���̵�����
//		&pi); // ��һ��out����������PROCESS_INFORMATION�ṹ������������̴�����Ľ��� ���������ID�����߳̾���Լ����߳�ID	
//
//}


//ͨ�������д�������
//���������е�������Ϊһ���ַ�������CreateProcess�ĵڶ���������
//VOID TestCreateProcessByCmdline()
//{
//	STARTUPINFO si = { 0 };
//	PROCESS_INFORMATION pi;
//
//	si.cb = sizeof(si);
//	        
//	TCHAR szCmdline[] = TEXT("c://program files//internet explorer//iexplore.exe http://www.4399.com"); //�������Ͳ���֮��ӿո�    
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

//�����кͳ��������ʹ��
//VOID TestCreateProcess()
//{
//    STARTUPINFO si = { 0 };
//    PROCESS_INFORMATION pi;
//    si.cb = sizeof(si);
//    TCHAR szCmdline[] = TEXT(" http://www.4399.com");
//
//    BOOL res = CreateProcess(
//        TEXT("c://program files//internet explorer//iexplore.exe"),       //��ie      
//        szCmdline,         //ͨ�������д���ie�õ�����ַ        
//        NULL,
//        NULL,
//        FALSE,
//        CREATE_NEW_CONSOLE,
//        NULL,
//        NULL, &si, &pi);
//}

int main01()
{
	//TestCreateProcessByAPPName(); ͨ�� �������ƴ�������

	//TestCreateProcessByCmdline(); //ͨ�� �����д�������

    //TestCreateProcess();

	return 0;
}


int main(int argc, char* argv[])
{
	char szBuffer[256] = { 0 };
	char szHandle[8] = { 0 };

	//��Ҫ�����ܼ̳еľ���������̱���ָ��һ��SECURITY_ATTRIBUTES�ṹ���������г�ʼ��
	//������Ա�����壺 ��С��Ĭ�ϰ�ȫ���ԡ��Ƿ���Լ̳�
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	//����һ�����Ա��̳е��ں˶���
	HANDLE g_hEnvent = CreateEvent(&sa, TRUE, FALSE, NULL);

	//��֯�����в���
	sprintf(szHandle, "%x", g_hEnvent);
	sprintf(szBuffer, "D://XXXXXX.exe %s", szHandle);

	//���崴��������Ҫ�õĽṹ��
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);

	// �����ӽ���
	BOOL res = CreateProcess(
		NULL,
		(LPWSTR)szBuffer,
		NULL,
		NULL,
		TRUE,           //TRUE��ʱ��˵���ӽ��̿��Լ̳и����̵ľ����
		CREATE_NEW_CONSOLE,
		NULL,
		NULL, &si, &pi);

	//�����¼�Ϊ��֪ͨ
	SetEvent(g_hEnvent);
	//�رվ�� �ں˶��󲢲��ᱻ����
	CloseHandle(g_hEnvent);
						
	return 0;

}
