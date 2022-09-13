
#include <windows.h>
#include <stdio.h>  
#include <tchar.h>        // TCHAR  �������� ͷ�ļ�  
#include "resource.h"    

//�ı�����
HWND hRes;
HWND hBuf[2];  //������
HWND hTxt[4];  //������

//�ٽ���
CRITICAL_SECTION cs;

//�ź���
HANDLE hSemaphoreCust;
HANDLE hSemaphoreProd;

//�߳̾��
HANDLE hThread[5];

//�������߳�
DWORD WINAPI ThreadProcProd(LPVOID lpParameter)
{
    //��ȡ��Դ
    TCHAR szBuffer[256];
    memset(szBuffer, 0, 256 * sizeof(TCHAR));
    ::GetWindowText(hRes, szBuffer, 256);

    //���ַ�д�뵽������
    DWORD len = _tcslen(szBuffer);    //��ȡ�ַ�������
    for (int i = 0; i < len; i++) 
    {
        ::WaitForSingleObject(hSemaphoreProd, INFINITE);    //�ȴ��������ź���

        EnterCriticalSection(&cs);   //��ȡ����

        TCHAR szBuf[256];

        TCHAR szTmp[2];
        memset(szTmp, 0, 2 * sizeof(TCHAR));
        memcpy(szTmp, szBuffer + i, sizeof(TCHAR));    //�ַ���������ʱ������
        for (int j = 0; j < 2; j++) {
            memset(szBuf, 0, 256 * sizeof(TCHAR));
            ::GetWindowText(hBuf[j], szBuf, 256 * sizeof(TCHAR));
            if (_tcscmp(szBuf, TEXT("0")) == 0) {    //�������һ��������Ϊ0�����
                ::SetWindowText(hBuf[j], szTmp);
                break;
            }
        }

        ::ReleaseSemaphore(hSemaphoreCust, 1, NULL);    //ÿ�η���֮���ͷ�һ���������ź���
        LeaveCriticalSection(&cs);
    }

    return 0;
}

//�������߳�
DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
    DWORD index = (DWORD)lpParameter;
    while (TRUE) {
        ::WaitForSingleObject(hSemaphoreCust, INFINITE);

        EnterCriticalSection(&cs);   //��ȡ����

        //�ӻ������ж�ȡ��ĸ
        TCHAR szTmp[2];
        memset(szTmp, 0, 2 * sizeof(TCHAR));
        for (int i = 0; i < 2; i++) {    //������������������һ����Ϊ0�ʹ������
            ::GetWindowText(hBuf[i], szTmp, 2);
            if (_tcscmp(szTmp, TEXT("0")) != 0) {

                Sleep(1000);
                //д���Լ����ı���
                TCHAR szBuffer[256];
                memset(szBuffer, 0, 256 * sizeof(TCHAR));
                ::GetWindowText(hTxt[index], szBuffer, 256);
                DWORD len = _tcslen(szBuffer);
                TCHAR buf[256];
                memset(buf, 0, 256 * sizeof(TCHAR));
                memcpy(buf, TEXT("_"), sizeof(TCHAR));
                memcpy(buf + 1, szTmp, sizeof(TCHAR));
                memcpy(buf + 2, szBuffer, len * sizeof(TCHAR));
                ::SetWindowText(hTxt[index], buf);

                //��������0
                ::SetWindowText(hBuf[i], TEXT("0"));
                Sleep(500);

                break;
            }
        }
        ::ReleaseSemaphore(hSemaphoreProd, 1, NULL);
        LeaveCriticalSection(&cs);
    }
    return 0;
}


//�̺߳���
DWORD WINAPI ThreadBegin(LPVOID lpParameter)
{
    hSemaphoreProd = CreateSemaphore(NULL, 2, 2, NULL);        //�������ź���,��ʼ��2���ź�
    hSemaphoreCust = CreateSemaphore(NULL, 0, 2, NULL);        //�������ź���

    InitializeCriticalSection(&cs);        //��ʼ���ٽ���

    //�����������߳�
    hThread[0] = ::CreateThread(NULL, 0, ThreadProc, (void*)0, 0, NULL);
    hThread[1] = ::CreateThread(NULL, 0, ThreadProc, (void*)1, 0, NULL);
    hThread[2] = ::CreateThread(NULL, 0, ThreadProc, (void*)2, 0, NULL);
    hThread[3] = ::CreateThread(NULL, 0, ThreadProc, (void*)3, 0, NULL);
    //�����������߳�
    hThread[4] = ::CreateThread(NULL, 0, ThreadProcProd, NULL, 0, NULL);

    //�ͷ��ź���
    ::WaitForMultipleObjects(5, hThread, TRUE, INFINITE);            //��5���߳����������Զ�������֪ͨ״̬����ʱ�ر��ź���
    ::CloseHandle(hSemaphoreProd);
    ::CloseHandle(hSemaphoreProd);
    return 0;
}

//�ص�����            
BOOL CALLBACK MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    BOOL bRet = FALSE;
    switch (uMsg)
    {
    case WM_CLOSE:
    {
        EndDialog(hDlg, 0);
        break;
    }
    case WM_INITDIALOG:
    {
        //��ȡ�ı�����
        hRes = GetDlgItem(hDlg, IDC_EDIT_1);
        hBuf[0] = GetDlgItem(hDlg, IDC_EDIT_2);
        hBuf[1] = GetDlgItem(hDlg, IDC_EDIT_3);
        hTxt[0] = GetDlgItem(hDlg, IDC_EDIT_4);
        hTxt[1] = GetDlgItem(hDlg, IDC_EDIT_5);
        hTxt[2] = GetDlgItem(hDlg, IDC_EDIT_6);
        hTxt[3] = GetDlgItem(hDlg, IDC_EDIT_7);

        //��ʼ���ı���
        ::SetWindowText(hRes, TEXT("0"));
        ::SetWindowText(hBuf[0], TEXT("0"));
        ::SetWindowText(hBuf[1], TEXT("0"));

        break;
    }
    case WM_COMMAND:

        switch (LOWORD(wParam))
        {
        case IDC_BUTTON:
        {
            ::CreateThread(NULL, 0, ThreadBegin, NULL, 0, NULL);
            return TRUE;
        }
        }
        break;
    }

    return bRet;
}


//��ں���             
int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nCmdShow)
{
    DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, MainDlgProc);
    return 0;
}