#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>


 //������ 
int main(int argc, char* argv[])
{
	//��Ҫ�����ܼ̳еľ���������̱���ָ��һ��SECURITY_ATTRIBUTES�ṹ���������г�ʼ��							
	//������Ա�����壺��С��Ĭ�ϰ�ȫ���ԡ��Ƿ���Լ̳�							
	char szBuffer[256] = { 0 };
	char szHandle[8] = { 0 };
	//��Ҫ�����ܼ̳еľ���������̱���ָ��һ��SECURITY_ATTRIBUTES�ṹ���������г�ʼ��
	//������Ա�����壺��С��Ĭ�ϰ�ȫ���ԡ��Ƿ���Լ̳�
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	//����һ�����Ա��̳е��ں˶���
	HANDLE hEvent = CreateEvent(&sa, TRUE, FALSE, NULL);

	//��֯�����в���
	sprintf(szHandle, "%x", hEvent);
     
	// ·��ƴ�� �������ʱ��Ҫ �ÿո� ����
	sprintf(szBuffer, "D:\\XXX.exe %zx", szHandle);   // %zx  z��ʾ size_t :32λ �޷���4�ֽ� ; 64λ �޷���8�ֽ�

	//���崴��������Ҫ�Ľṹ��
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);

	//�����ӽ���
	BOOL res = CreateProcessA(
		NULL,				//Ӧ�ó�������
		szBuffer,			//�������ַ���
		NULL,				//�̰߳�ȫ����
		NULL,				//���̰�ȫ����
		TRUE,				// �Ƿ�̳и����̵�����
		CREATE_NEW_CONSOLE, // ������־
		NULL,				// ָ���µĻ������ָ��
		NULL,				// ָ��ǰĿ¼����ָ��
		&si,				// ���ݸ��½��̵���Ϣ
		&pi					// �½��̷��ص���Ϣ
		);
	
	//�����¼�Ϊ��֪ͨ
	SetEvent(hEvent);

	//�رվ�� �ں˶��󲢻᲻�ᱻ����
	CloseHandle(hEvent);

	return 0;
}

//�ӽ���
int main(int argc, char* argv[]) {

	printf("%s\n", argv[0]);

	HANDLE hEvent;
	sscanf(argv[1], "%zx", &hEvent);
	printf("%zx\n", hEvent);

	printf("��ʼ�ȴ�.....\n");
	//���¼������֪ͨʱ                 
	WaitForSingleObject(hEvent, INFINITE);
	DWORD dwCode = GetLastError();
	printf("�ȵ���Ϣ.....%x\n", dwCode);
	getchar();
	return 0;
}