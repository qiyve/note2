#pragma   comment(linker,"/subsystem:\"windows\"  /entry:\"mainCRTStartup\"") // ���ؿ���̨
#include<stdio.h>
#include<Windows.h>


//����ָ������
void test01()
{
  // MAX_PATH �� 260
	TCHAR szTitle[MAX_PATH] = { 0 };

	//����1 ClassName  ����2 �������ƣ��������ƣ�
	HWND hwnd = ::FindWindow(TEXT("#32770"), TEXT("�ɸ봫��  IP Messenger (IPMsg)"));

	if (hwnd != NULL)
	{
		//�޸Ĵ��ڱ���
		//������ 1 ���   | 2 �µı����ؼ��ı���
		::SetWindowText(hwnd, TEXT("�µĴ���"));
	}
	else
	{
		//������ 1 ��� | 2 Ҫ��ʾ������ | 3 �Ի������| 4 �Ի������ݺ���Ϊ
		::MessageBox(NULL, TEXT("����û���ҵ�"), TEXT("[ERROR]"), MB_OK); //MB_OK ��Ϣ�����һ����ť��ȷ��
	}

}

//���ڿ���
void test02()
{
	TCHAR siTitle[MAX_PATH] = { 0 };
	HWND hwnd = ::FindWindow(TEXT("#32770"), TEXT("�ɸ봫��  IP Messenger (IPMsg)"));

	if (hwnd != NULL)
	{
		//������ʹ��typedefֱ�Ӷ���ĺ���ָ��
		typedef void (WINAPI* PSWITCHTOTHISWINDOW)(HWND, BOOL);
 
      // ���溯��ָ�붨�����֮���൱���������ֱ��ʹ�ô��ź������͵�ָ��
      // PSWITCHTOTHISWINDOW�� ���⺯��ָ��ֱ��ʵ����
		PSWITCHTOTHISWINDOW SwitchToThisWindow;
 
		//ͨ��LordLibrary��ȡuser32.dll��ģ����
		HMODULE hUser32 = LoadLibrary("user32.dll"); // HMODULE Ӧ�ó��������ģ��

		// GetProcAddress ��ָ���Ķ�̬���ӿ� ��DLL�� �м��������ĺ�����Ҳ��Ϊ���̣�������ĵ�ַ��
		// ���� 1 ������������DLLģ��ľ�� |  ����2 ������������ƣ����������ֵ 
		// ʹ��GetproAddess ��ȡ��Ҫ�ĺ�����ַ��Ȼ�������ַ������ָ��
		SwitchToThisWindow = (PSWITCHTOTHISWINDOW)GetProcAddress(hUser32, "SwitchToThisWindow");

		Sleep(2000);
		//�л�����
		//����� user32.dll ���л����ں�����ַ�ó����ˣ����ڵ��ú���ָ���л�����
		SwitchToThisWindow(hwnd, true);
 
		Sleep(2000);
		//�رմ���
		::SendMessage(hwnd, WM_CLOSE, 0, 0);
	}
	else
	{
		::MessageBox(NULL, TEXT("����û���ҵ�"), TEXT("[ERROR]"), MB_OK);
	}
}


//�����Ӵ���
void test03()
{
	
	TCHAR szTitle[MAX_PATH] = { 0 };

	HWND hwnd = ::FindWindow(TEXT("#32770"), TEXT("�ɸ봫��  IP Messenger (IPMsg)"));
	if (hwnd != NULL)
	{
		//�����Ӵ���	������������Ҫ���ҵ��Ӵ��ڵ����������ĸ�������Ҫ���ҵ��Ӵ��ڵı���						
		HWND hEdit = FindWindowEx(hwnd, NULL, "RichEdit20W", "");
		//����������������ͨ��Spy++�ҵ����࣬�����뵱Ȼ��дEdit�����ҵ����ĸ����������ǿ�

		//����Ĳ����������������ҵ���RichEdit20W���������ı��⣬��Ϊδ����֮ǰ�����ǿ�
		//���ñ���		 ʹ�ù���Spy++������֤����					
		::SetWindowText(hEdit, "�ı����µı���");
		//�޸�����							
		::SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)"�µ�����");
	}
	else
	{
		::MessageBox(NULL, TEXT("����û���ҵ�"), TEXT("[ERROR]"), MB_OK);
	}

}

//�����Ӵ��� ͨ���ؼ� id
void test04()
{

	TCHAR szTitle[MAX_PATH] = { 0 };
	HWND hwnd = ::FindWindow(TEXT("#32770"), TEXT("�ɸ봫��  IP Messenger (IPMsg)"));
	if (hwnd != NULL)
	{
		//��ȡ�Ӵ��ڵľ��
		HWND hEdit = ::GetDlgItem(hwnd, 0x3E9);
		//��ȡ����
		::SendMessage(hEdit, WM_GETTEXT, MAX_PATH, (LPARAM)szTitle);

		//��������
		::SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)"�����õ�����");
	}
	else
	{
		::MessageBox(NULL, TEXT("����û���ҵ�"), TEXT("Errors"), MB_OK);
	}
}

//ö���Ӵ��ڿؼ�
BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam)
{
	TCHAR szTitle[MAX_PATH] = { 0 };
	//��ȡ�����ı���ؼ��ı�
	::GetWindowText(hWnd, szTitle, MAX_PATH);
	MessageBox(NULL, szTitle, "[�Ӵ���]", MB_OK);
	return true;
}

VOID EnumChildWindow()
{
	TCHAR szTitle[MAX_PATH] = { 0 };
	HWND hWnd = ::FindWindow(TEXT("#32770"), TEXT("�ɸ봫��  IP Messenger (IPMsg)"));
	if (hWnd != NULL)
	{
		::EnumChildWindows(hWnd, EnumChildProc, 0);
	}
	else
	{
		::MessageBox(NULL, TEXT("����û���ҵ�"), TEXT("[ERROR]"), MB_OK);
	}
}


//ö�����д򿪴���
BOOL CALLBACK EnumOpenWindowProc(HWND hWnd, LPARAM lParam)
{
	TCHAR szTitle[MAX_PATH] = { 0 };
	::GetWindowText(hWnd, szTitle, MAX_PATH);
	MessageBox(NULL, szTitle, "[����]", MB_OK);
	if (strcmp(szTitle, "�ɸ봫��  IP Messenger (IPMsg)") == 0)
	{
		MessageBox(NULL, szTitle, "[����]", MB_OK);
		return FALSE;
	}
	return TRUE;
}

VOID EnumOpenWindows()
{
	EnumWindows(EnumOpenWindowProc, NULL);
}

int main01()
{
	test01();
	test02();
	test03();
	test04();
	
	//ö���Ӵ���
	EnumChildWindow();

	//ö�����д򿪴���
	EnumOpenWindows();

	return 0;
}


//ģ����굥��
VOID TestMouseClick()
{
	TCHAR szTitle[MAX_PATH] = { 0 };
	//RECT �ṹͨ�������ϽǺ����½ǵ����궨����Ρ�
	RECT r;
	HWND hwnd = ::FindWindow(TEXT("#32770"), TEXT("�ɸ봫��  IP Messenger (IPMsg)"));
	if (hwnd != NULL)
	{
		HWND hButton = FindWindowEx(hwnd, NULL, "Button", "ˢ��(&R)");

		//��ȡ��������
		::GetWindowRect(hButton, &r);

		printf("%d %d\n", r.left, r.top); // r.left ���Ͻ� x���   r.left ���Ͻ�y����

		//��������λ��
		::SetCursorPos(r.left + 5, r.top + 5); //ֱ�ӻ�ȡ�������� button ���Ͻ� ���� ����ƫ��
		Sleep(3000);

		//����������
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);  //������  MOUSEEVENTF_LEFTDOWN ����ѹر�
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);	//�ɿ����  MOUSEEVENTF_LEFTUP	����Ѵ�
	}
	else
	{
		::MessageBox(NULL, TEXT("����û���ҵ�"), TEXT("[ERROR]"), MB_OK);
	}

}


//ģ�����
VOID Testmnkeyboard()
{
	TCHAR szTiTle[MAX_PATH] = { 0 };
	RECT r;
	HWND hwnd = ::FindWindow(TEXT("#32770"), TEXT("�ɸ봫��  IP Messenger (IPMsg)"));
	if (hwnd != NULL)
	{
		//HWND hButton = FindWindowEx(hwnd, NULL, "Button", "ˢ��(&R)");
		HWND hEdit = ::GetDlgItem(hwnd, 0x3E9);

		/// ��ȡ��������
		::GetWindowRect(hEdit, &r);

		//��ȡ����λ��
		::SetCursorPos(r.left + 1, r.top + 1);
		Sleep(3000); //���ﾡ����ʱ����΢��һ�� ���ⷭ����ִ���ƶ���� ���Լ� û���ɿ��������ֳ�ͻ

		//����������
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);  //������  MOUSEEVENTF_LEFTDOWN ����ѹر�
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);	//�ɿ����  MOUSEEVENTF_LEFTUP	����Ѵ�

		//ģ�����
		keybd_event(97, 0, 0, 0);
		keybd_event(97, 0, KEYEVENTF_KEYUP, 0);
		Sleep(1000);
		keybd_event(66, 0, 0, 0);
		keybd_event(66, 0, KEYEVENTF_KEYUP, 0); // KEYEVENTF_KEYUP ���ָ�������ͷ���Կ�����δָ�������������
		Sleep(1000);
		keybd_event(16, 0, 0, 0);
		keybd_event(67, 0, 0, 0);
		keybd_event(67, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(16, 0, KEYEVENTF_KEYUP, 0);
	}
	else
	{
		::MessageBox(NULL, TEXT("����û���ҵ�"), TEXT("[ERROR]"), MB_OK);
	}

}



int main()
{
	//TestMouseClick();

	Testmnkeyboard();

	return 0;
}
