#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include"resource.h"


//�����ı��Ի�����
HWND hongbao;  //IDC_EDIT_1  �洢��������Ի���
HWND zg;  //IDC_EDIT_2   ������߳�1
HWND wst;  //IDC_EDIT_3  ������߳�2
HWND smy;  //IDC_EDIT_4  ������߳�3

//�����ٽ����ṹ����
CRITICAL_SECTION cs;
DWORD num;   //���ֵ

//  zg 
DWORD WINAPI ThreadProc1(LPVOID lpParameter)
{
	while (num > 0)
	{
		//��������
		EnterCriticalSection(&cs);
		//��ȡ ��� �ı�������
		CHAR szBuffer[10];
		memset(szBuffer, 0, 10);
		GetWindowTextA(hongbao, szBuffer, 10);

		//��ȡ zg �ı��Ի�������
		CHAR zgBuffer[10];
		memset(zgBuffer, 0, 10);
		GetWindowTextA(zg, zgBuffer, 10);

		//�ַ���ת����
		sscanf(szBuffer, "%d", &num);
		DWORD zgNum; //�洢�����ĺ��ֵ
		sscanf(zgBuffer, "%d", &zgNum);
		if (num >= 50)
		{
			memset(szBuffer, 0, 10);
			memset(zgBuffer, 0, 10);
			//ÿ���� 50��
			num -= 50;
			zgNum += 50;
			//����ת�ַ�
			sprintf(szBuffer, "%d", num);
			sprintf(zgBuffer, "%d", zgNum);
			//д���ı��Ի���
			SetWindowTextA(hongbao, szBuffer);
			SetWindowTextA(zg, zgBuffer);
		}
		LeaveCriticalSection(&cs);
		Sleep(1000);
	}
	return 0;
}

//wst
DWORD WINAPI ThreadProc2(LPVOID lpParameter)
{
	while (num > 0)
	{
		//��������
		EnterCriticalSection(&cs);
		//��ȡ ��� �ı�������
		CHAR szBuffer[10];
		memset(szBuffer, 0, 10);
		GetWindowTextA(hongbao, szBuffer, 10);

		//��ȡ wst �ı��Ի�������
		CHAR zgBuffer[10];
		memset(zgBuffer, 0, 10);
		GetWindowTextA(wst, zgBuffer, 10);

		//�ַ���ת����
		sscanf(szBuffer, "%d", &num);
		DWORD zgNum; //�洢�����ĺ��ֵ
		sscanf(zgBuffer, "%d", &zgNum);
		if (num >= 50)
		{
			memset(szBuffer, 0, 10);
			memset(zgBuffer, 0, 10);
			//ÿ���� 50��
			num -= 50;
			zgNum += 50;
			//����ת�ַ�
			sprintf(szBuffer, "%d", num);
			sprintf(zgBuffer, "%d", zgNum);
			//д���ı��Ի���
			SetWindowTextA(hongbao, szBuffer);
			SetWindowTextA(wst, zgBuffer);
		}
		LeaveCriticalSection(&cs);
		Sleep(1000);
	}
	return 0;
}

//smy
DWORD WINAPI ThreadProc3(LPVOID lpParameter)
{
	while (num > 0)
	{
		//��������
		EnterCriticalSection(&cs);
		//��ȡ ��� �ı�������
		CHAR szBuffer[10];
		memset(szBuffer, 0, 10);
		GetWindowTextA(hongbao, szBuffer, 10);

		//��ȡ wst �ı��Ի�������
		CHAR zgBuffer[10];
		memset(zgBuffer, 0, 10);
		GetWindowTextA(smy, zgBuffer, 10);

		//�ַ���ת����
		sscanf(szBuffer, "%d", &num);
		DWORD zgNum; //�洢�����ĺ��ֵ
		sscanf(zgBuffer, "%d", &zgNum);
		if (num >= 50)
		{
			memset(szBuffer, 0, 10);
			memset(zgBuffer, 0, 10);
			//ÿ���� 50��
			num -= 50;
			zgNum += 50;
			//����ת�ַ�
			sprintf(szBuffer, "%d", num);
			sprintf(zgBuffer, "%d", zgNum);
			//д���ı��Ի���
			SetWindowTextA(hongbao, szBuffer);
			SetWindowTextA(smy, zgBuffer);
		}
		LeaveCriticalSection(&cs);
		Sleep(1000);
	}
	return 0;
}


//�̺߳���
DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	//��ʼ������
	InitializeCriticalSection(&cs);

	//�����߳�
	HANDLE hThread1 = ::CreateThread(NULL, 0, ThreadProc1, NULL, 0, NULL);
	HANDLE hThread2 = ::CreateThread(NULL, 0, ThreadProc2, NULL, 0, NULL);
	HANDLE hThread3 = ::CreateThread(NULL, 0, ThreadProc3, NULL, 0, NULL);

	return 0;
}

//�ص�����  ��Ϣ����
BOOL CALLBACK DialogProc(HWND   hwndDlg,
						 UINT   uMsg,
						 WPARAM wParam,
						 LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		{
			hongbao = GetDlgItem(hwndDlg, IDC_EDIT_1); //��ȡ����Ի�����
			zg = GetDlgItem(hwndDlg, IDC_EDIT_2);    // ��ȡǿ����Ի���1 ���
			wst = GetDlgItem(hwndDlg, IDC_EDIT_3);     // 2
			smy = GetDlgItem(hwndDlg, IDC_EDIT_4);    // 3

			//��ʼ��ֵ
			SetWindowText(hongbao, TEXT("1000"));
			SetWindowText(zg, TEXT("0"));
			SetWindowText(wst, TEXT("0"));
			SetWindowText(smy, TEXT("0"));

			return TRUE;
		}

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1:
			{
				//��ȡ�ı��Ի�������
				CHAR szBuffer[10];
				memset(szBuffer, 0, 10);
				GetWindowTextA(hongbao, szBuffer, 10);
				//�ַ�ת����
				sscanf(szBuffer, "%d", &num);

				//��������
				SetWindowText(zg, TEXT("0"));
				SetWindowText(wst, TEXT("0"));
				SetWindowText(smy, TEXT("0"));

				HANDLE hThread = ::CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
				//������������ط������� �رվ��
				::CloseHandle(hThread);
				return TRUE;
			}

		}
		break;
	case WM_CLOSE: //�˳�
		EndDialog(hwndDlg, 0);
		return TRUE;
	}
	

	return FALSE;
}
int CALLBACK WinMain(HINSTANCE hInstance,
				   	 HINSTANCE hPrevHinstance,
					 LPSTR	   lpCmdLine,
					 int	   nCmdShow)
{
	//�����Ի��򴰿�
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, DialogProc);

	return 0;
}