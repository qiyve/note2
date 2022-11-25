#include<windows.h>
#include<stdio.h>
#include "resource.h"

HANDLE g_hEvent; // �¼�
// �ı��Ի�����
HWND hEdit1;
HWND hEdit2;
HWND hEdit3;
HWND hEdit4;

DWORD WINAPI ThreadProc2(LPVOID lpParameter)
{
	TCHAR szBuffer[10] = { 0 };//��ʼ��Ϊ0

	//�ȴ��¼������֪ͨʱ
	WaitForSingleObject(g_hEvent, INFINITE); // INFINITE:  -1  ��ʾһֱ�ȴ�
	//��ȡ����
	GetWindowText(hEdit1, szBuffer, 10);
	SetWindowText(hEdit2, szBuffer); //д��  hEdit2 �ı�����
	Sleep(1000);
	//�����¼�Ϊ��֪ͨ״̬
	//SetEvent(g_hEvent);
	return 0;
}

DWORD WINAPI ThreadProc3(LPVOID lpParameter)
{
	TCHAR szBuffer[10] = { 0 };

	//�ȴ��¼���Ϊ��֪ͨ״̬
	WaitForSingleObject(g_hEvent, -1);
	//��ȡ��һ���ı����ֵ  д�ص� 3 �ı���
	GetWindowText(hEdit1, szBuffer, 10);
	SetWindowText(hEdit3, szBuffer);

	Sleep(1000);
	//�����¼�Ϊ��֪ͨ״̬
	//SetEvent(g_hEvent);
	return 0;
}

DWORD WINAPI ThreadProc4(LPVOID lpParameter)
{
	TCHAR szBuffer[10] = { 0 };

	//�ȴ��¼���Ϊ��֪ͨ״̬
	WaitForSingleObject(g_hEvent, -1);
	//��ȡ��һ���ı����ֵ  д�ص� 4 �ı���
	GetWindowText(hEdit1, szBuffer, 10);
	SetWindowText(hEdit4, szBuffer);

	Sleep(1000);
	//�����¼�Ϊ��֪ͨ״̬
	//SetEvent(g_hEvent);
	return 0;
}

//�̺߳��� �����߳�
DWORD WINAPI ThreadProc_1(LPVOID lpParameter)
{
	//�����¼�
	//1��Ĭ�ϰ�ȫ����   2��(TRUE) ��Ҫ�ֶ�����Ϊδ֪ͨ״̬  FLASE��ֻҪ���߳�wait���˸��¼�������Ὣ���¼���״̬�Ļ�ȥ���δ֪ͨ״̬
	//3����ʼ״̬δ֪ͨ  4����
	g_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	//g_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	HANDLE hThread[3];
	//����3���߳�
	hThread[0] = CreateThread(NULL, 0, ThreadProc2, NULL, 0, NULL);
	hThread[1] = CreateThread(NULL, 0, ThreadProc3, NULL, 0, NULL);
	hThread[2] = CreateThread(NULL, 0, ThreadProc4, NULL, 0, NULL);

	//�����ı����ֵ
	SetWindowText(hEdit1, TEXT("1000"));

	//�����¼�Ϊ��֪ͨ״̬
	SetEvent(g_hEvent);
	//�ȴ��߳̽��� �����ں˶���
	WaitForMultipleObjects(3, hThread, TRUE, INFINITE);
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	CloseHandle(hThread[2]);
	CloseHandle(g_hEvent);

	return 0;
}

//�ص�����
BOOL CALLBACK DialogProc(
			HWND	 hwndDlg,
			UINT	 uMsg,
			WPARAM   wParam,
			LPARAM   lParam
)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		{
			hEdit1 = GetDlgItem(hwndDlg, IDC_EDIT_1);
			hEdit2 = GetDlgItem(hwndDlg, IDC_EDIT_2);
			hEdit3 = GetDlgItem(hwndDlg, IDC_EDIT_3);
			hEdit4 = GetDlgItem(hwndDlg, IDC_EDIT_4);
			return TRUE;
		}
			
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON:
			{	
				//���ⴴ��һ���߳������������̣߳���ֹ���߳�����
				HANDLE hThread = ::CreateThread(NULL, 0, ThreadProc_1, NULL, 0, NULL);
				//������������ĵط������� �رվ��
				::CloseHandle(hThread);
				return TRUE;
			}
			return FALSE;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwndDlg, 0);
		return TRUE;
	}

	return FALSE;
}

int CALLBACK WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevHinstance,
					 LPSTR	   lpCmdLine,
					 int       nCmdShow)
{
	//�����Ի��򴰿�
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc);
}