#include<stdio.h>
#include<Windows.h>


//�������λ��

//ͨ����������QQ,ʵ���Զ���¼.		
void Open_ipmsg()
{
	//1��CreateProcess��������
	TCHAR szCmdline[] = TEXT("D:\\ipmsg.exe");
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi;

	BOOL res = CreateProcess(
		NULL,			 // Ӧ�ó�������
		szCmdline,		 // �������ַ���      
		NULL,			 // ���̵İ�ȫ���� 
		NULL,			 // �̵߳İ�ȫ���� 
		FALSE,		 	 // �Ƿ�̳и����̵�����  
		CREATE_NEW_CONSOLE,	// ������־  
		NULL,			// ָ���µĻ������ָ�� 
		NULL,			// ָ��ǰĿ¼����ָ�� 
		&si,			// ���ݸ��½��̵���Ϣ
		&pi				// �½��̷��ص���Ϣ     
	);
	Sleep(4000);//�ȴ�ipmsg.exe��


	//2���������д򿪴��ڣ��ȴ�������
	TCHAR szTitle[MAX_PATH] = { 0 };
	HWND hwnd = ::FindWindow(TEXT("#32770"), TEXT("�ɸ봫��  IP Messenger (IPMsg)"));

	if (hwnd != NULL)
	{
		//��QQ ����ǰ̨  ���庯��ָ��
		typedef void (WINAPI* PSWITCHTOTHISWINDOW)(HWND, BOOL);
		//����ָ��ʵ����
		PSWITCHTOTHISWINDOW SwichToThisWindow;

		//ͨ��LoadLibrary ��ȡ user32.dll ��ģ����
		HMODULE hUser32 = LoadLibrary("user32.dll");

		// ʹ��GetproAddess ��ȡ��Ҫ�ĺ�����ַ��Ȼ�������ַ������ָ��
		SwichToThisWindow = (PSWITCHTOTHISWINDOW)GetProcAddress(hUser32, "SwitchToThisWindow");

		Sleep(2000);
		//�л����� 
		SwichToThisWindow(hwnd, true);

		//3���������λ�ã����
		RECT r;
		HWND hEdit = GetDlgItem(hwnd, 0x3E9);

		//��ȡ���������ַ
		::GetWindowRect(hEdit, &r);

		//��ȡ����λ��
		::SetCursorPos(r.left + 1, r.top + 1);
		Sleep(3000);

		//�����������
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

		//ģ��������� �� �˺� ����
		keybd_event(49, 0, 0, 0);			// 1
		keybd_event(49, 0, KEYEVENTF_KEYUP, 0);	 // ����
		Sleep(1000);
		keybd_event(56, 0, 0, 0);			// 8 
		keybd_event(56, 0, KEYEVENTF_KEYUP, 0);
		Sleep(1000);
		keybd_event(55, 0, 0, 0);			// 7
		keybd_event(55, 0, KEYEVENTF_KEYUP, 0);
		Sleep(1000);
		keybd_event(50, 0, 0, 0);			// 2
		keybd_event(50, 0, KEYEVENTF_KEYUP, 0);
		Sleep(1000);
		keybd_event(54, 0, 0, 0);			// 6
		keybd_event(54, 0, KEYEVENTF_KEYUP, 0);
		Sleep(1000);
		keybd_event(54, 0, 0, 0);			// 6
		keybd_event(54, 0, KEYEVENTF_KEYUP, 0);

		keybd_event(13, 0, 0, 0);
		keybd_event(13, KEYEVENTF_KEYUP, 0, 0); // �س�  ����

		keybd_event(16, 0, 0, 0);  // A
		keybd_event(65, 0, 0, 0);  // Shift
		keybd_event(65, 0, KEYEVENTF_KEYUP, 0); // ����
		keybd_event(16, 0, KEYEVENTF_KEYUP, 0);
		Sleep(1000);
		keybd_event(66, 0, 0, 0);  // b
		keybd_event(66, 0, KEYEVENTF_KEYUP, 0);
		Sleep(1000);
		keybd_event(67, 0, 0, 0);  // c
		keybd_event(67, 0, KEYEVENTF_KEYUP, 0);

		//�������
		HWND Button = FindWindowEx(hwnd, NULL, TEXT("Button"), TEXT("����(&S)"));
		//��ȡȥ��ťλ��
		::GetWindowRect(Button, &r);
		//��ȡ���λ��
		::SetCursorPos(r.left + 5, r.top + 5);

		//�����������
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

		//���������
		HWND preson = FindWindowEx(hwnd, NULL, TEXT("SysListView32"), TEXT("List1"));
		//��ȡȥ��ťλ��
		::GetWindowRect(preson, &r);
		//��ȡ���λ��
		::SetCursorPos(r.left + 5, r.top + 10);

		//�����������
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	}
	else
	{
		::MessageBox(NULL, TEXT("δ�ҵ�����"), TEXT("[ERROR]"), MB_OK);
	}
}

int main()
{
	Open_ipmsg();

	return 0;
}