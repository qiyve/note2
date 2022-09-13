#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include"resource.h"


HANDLE hSemaphore;	//�����ź������ �ź���Ҳ���ں˶���
HANDLE hThread[3];  //�����ں�����

//�������
HWND hEditSet;
HWND hEdit1;
HWND hEdit2;
HWND hEdit3;


DWORD WINAPI ThreadProc1(LPVOID lpParameter)
{
	CHAR szBuffer[10];
	DWORD dwNum = 0;

	//�ȴ�
	WaitForSingleObject(hSemaphore, INFINITE);
	while (dwNum < 100)
	{
		Sleep(100);
		memset(szBuffer, 0, 10);
		GetWindowTextA(hEdit1, szBuffer, 10); //��ȡ�ı����ֵ
		sscanf(szBuffer, "%d", &dwNum);       //�ַ�ת����
		dwNum++;
		memset(szBuffer, 0, 10);
		sprintf(szBuffer, "%d", dwNum);		 //����ת�ַ�
		SetWindowTextA(hEdit1, szBuffer);	 //д���ı���
	}
	ReleaseSemaphore(hSemaphore, 1, NULL);
	return 0;
}

DWORD WINAPI ThreadProc2(LPVOID lpParameter)
{
	CHAR szBuffer[10];
	DWORD dwNum = 0;

	//�ȴ�
	WaitForSingleObject(hSemaphore, INFINITE);
	while (dwNum < 100)
	{
		Sleep(100);
		memset(szBuffer, 0, 10);
		GetWindowTextA(hEdit2, szBuffer, 10); //��ȡ�ı����ֵ
		sscanf(szBuffer, "%d", &dwNum);       //�ַ�ת����
		dwNum++;
		memset(szBuffer, 0, 10);
		sprintf(szBuffer, "%d", dwNum);		 //����ת�ַ�
		SetWindowTextA(hEdit2, szBuffer);	 //д���ı���
	}
	ReleaseSemaphore(hSemaphore, 1, NULL);
	return 0;
}

DWORD WINAPI ThreadProc3(LPVOID lpParameter)
{
	CHAR szBuffer[10];
	DWORD dwNum = 0;

	//�ȴ�
	WaitForSingleObject(hSemaphore, INFINITE);
	while (dwNum < 100)
	{
		Sleep(100);
		memset(szBuffer, 0, 10);
		GetWindowTextA(hEdit3, szBuffer, 10); //��ȡ�ı����ֵ
		sscanf(szBuffer, "%d", &dwNum);       //�ַ�ת����
		dwNum++;
		memset(szBuffer, 0, 10);
		sprintf(szBuffer, "%d", dwNum);		 //����ת�ַ�
		SetWindowTextA(hEdit3, szBuffer);	 //д���ı���
	}
	ReleaseSemaphore(hSemaphore, 1, NULL);
	return 0;
}

// �̺߳��� 
DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	CHAR szBuffer[10];
	DWORD dwNum = 0;

	//�����ź���
	// 1. ��ȫ����  2.��ʼ����Դ���� Ϊ0ʱ�������ź� 3.��󲢷����� 4.��ʾ�ź��������� NULL��ʾ�����ź���
	hSemaphore = CreateSemaphore(NULL, 0, 3, NULL);

	//�����߳�
	hThread[0] = ::CreateThread(NULL, 0, ThreadProc1, NULL, 0, NULL);
	hThread[1] = ::CreateThread(NULL, 0, ThreadProc2, NULL, 0, NULL);
	hThread[2] = ::CreateThread(NULL, 0, ThreadProc3, NULL, 0, NULL);

	//
	while (dwNum < 1000)
	{
		memset(szBuffer, 0, 10);
		GetWindowTextA(hEditSet, szBuffer, 10);
		sscanf(szBuffer, "%d", &dwNum);
		dwNum++;
		memset(szBuffer, 0, 10);
		sprintf(szBuffer, "%d", dwNum);
		SetWindowTextA(hEditSet, szBuffer);
	}
	ReleaseSemaphore(hSemaphore, 2, NULL); //����2���ź����������ǵȴ�hSemaphore�������߳̿�ʼ����

	::WaitForMultipleObjects(3, hThread, TRUE, INFINITE);//��3���߳���������Զ�������֪ͨ״̬����ʱ�ر��ź���
	::CloseHandle(hSemaphore);

	return 0;
}

//�ص�����
BOOL CALLBACK MainDlgProc(
		HWND	hDlg,
		UINT	uMsg,
		WPARAM wParam,
		LPARAM lParam
	)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		{
			EndDialog(hDlg, 0);
			return TRUE;
		}
	case WM_INITDIALOG:
		{
			//��ȡ���
			hEditSet = GetDlgItem(hDlg, IDC_EDIT1);
			hEdit1 = GetDlgItem(hDlg, IDC_EDIT2);
			hEdit2 = GetDlgItem(hDlg, IDC_EDIT3);
			hEdit3 = GetDlgItem(hDlg, IDC_EDIT4);

			//��ʼ���ı�Ϊ0
			SetWindowText(hEditSet, TEXT("0"));
			SetWindowText(hEdit1, TEXT("0"));
			SetWindowText(hEdit2, TEXT("0"));
			SetWindowText(hEdit3, TEXT("0"));

			break;
		}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1:
			{
				////���ⴴ��һ���߳������������̣߳���ֹ���߳�����
				CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
				return TRUE;
			}
		}
		break;
	}
	return FALSE;
}

int APIENTRY WinMain( HINSTANCE hInstance,
					  HINSTANCE hPrevInstance,
					  LPSTR		lpComLine,
					  int		nCmdShow

)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, MainDlgProc);
	return 0;
}

