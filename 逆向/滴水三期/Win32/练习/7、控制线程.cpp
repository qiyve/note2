#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include"resource.h"


HWND  hEdit1;
HANDLE hThread;
int x = 0;

DWORD WINAPI ThreadProc( LPVOID lpParameter ) // thread data
{
    CHAR szBuffer[10];
    DWORD dwIndex = 0;
    DWORD dwCount;

    while (dwIndex < 100)
    {
        // ��һ�� �÷�ʽ����ͬ���̵߳Ķ�ջһ���ͷŵ�
       // ::ExitThread(1); ����Ϊָ���̵߳��˳��룬����ͨ��GetExitCodeThread ���鿴
      /*   if (dwIndex == 30)
        {
            ::ExitThread(0);
        }*/

        //�ڶ��� 2.�̺߳�������  ����
    /*    if (x == 1)
        {
            break;
        }*/

        GetWindowTextA(hEdit1, (LPSTR)szBuffer, 10);
        sscanf(szBuffer, "%d", &dwCount);
        dwCount++;
        Sleep(200);
        memset(szBuffer, 0, 10);
        sprintf(szBuffer, "%d", dwCount);
        SetWindowTextA(hEdit1, (LPCSTR)szBuffer);
        dwIndex++;
    }
    // 2.д�Լ������ͷ���Դ�Ĵ���....

    return 0;
}
//��Ϣ����
BOOL CALLBACK MainDlgProc(
    HWND hDlg,  //�Ի�����
    UINT uMsg,     //��Ϣ message
    WPARAM wParam, //��һ����Ϣ���� ��һ����Ϣ����
    LPARAM lParam
)
{
    DWORD Ret = FALSE;
    switch (uMsg)
    {
    case WM_CLOSE:
    {
        EndDialog(hDlg, 0);
        break;
    }
    case WM_INITDIALOG:
    {
        //��ȡ��ǰ�ı��� ���
        hEdit1 = GetDlgItem(hDlg, IDC_EDIT1);
        SetWindowTextA(hEdit1, LPCSTR("0"));
        return TRUE;
    }

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1:
        {
            //����һ���µ��߳�				
            hThread = ::CreateThread(NULL, 0, ThreadProc,
                NULL, 0, NULL);
            // ������������ĵط������� �رվ��	 ����Ӱ���߳�			
            //::CloseHandle(hThread);
            return TRUE;
        }
        case IDC_BUTTON2:  //����
        {
            ::SuspendThread(hThread); //���� ��Ҫ������߳̾��
            return TRUE;
        }
        case IDC_BUTTON3: //�ָ�
        {
            ::ResumeThread(hThread);
            return TRUE;
        }
        case IDC_BUTTON4: //��ֹ
        {
            //������  �첽 
            ::TerminateThread(hThread, 2);
            ::WaitForSingleObject(hThread, INFINITE); //�ȴ�ָ���Ķ������ź�״̬��ʱ�����ȥ��
            return TRUE;
        }
        break;
        }
    }
    return Ret;
}

int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR      lpCmdLine,
    int       nCmdShow)
{
    DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, MainDlgProc);
}