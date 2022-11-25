#include<stdio.h>
#include <windows.h>

DWORD WINAPI ThreadProc1(LPVOID lpParameter)
{
	for (int i = 0; i <1000; i++)
	{
		printf("+++++++++\n");
		Sleep(1000);
	}
	return 0;
}



int main01(int argc, char* argv[])
{

	//����һ���µ��߳�				
	HANDLE hThread1 = ::CreateThread(NULL, 0, ThreadProc1,
		NULL, 0, NULL);

	//����1���ں˶������������ǽ��̣�Ҳ�������߳�    //����2���ȴ�ʱ�䣬��λ����   INFINITE -1  ��ʾһֱ��
	// ��ʱ���� 0x102
	DWORD dwCode = ::WaitForSingleObject(hThread1, 1000);
	printf("%x\n", dwCode);
	MessageBox(0, 0, 0, 0);

	return 0;
}


DWORD WINAPI ThreadProc2(LPVOID lpParameter)
{
	for (int i = 0; i < 10; i++)
	{
		printf("+++++++++\n");
		Sleep(1000);
	}
	return 0;
}

DWORD WINAPI ThreadProc3(LPVOID lpParameter)
{
	for (int i = 0; i < 30; i++)
	{
		printf("---------\n");
		Sleep(1000);
	}

	return 0;
}


int main(int argc, char* argv[])
{
	
	HANDLE hArray[2];

	//����һ���µ��߳�						
	hArray[0] = ::CreateThread(NULL, 0, ThreadProc2,
		NULL, 0, NULL);

	//����һ���µ��߳�						
	hArray[1] = ::CreateThread(NULL, 0, ThreadProc3,
		NULL, 0, NULL);

	/*����1���ں˶��������� ����2���ں˶������飬   ����4����ʱʱ�� INFINITEһֱ�ȴ�
	����3���ȵ����� TRUE �ȵ����б�Ϊ��֪ͨ��FALSEֻҪ��һ����Ϊ��֪ͨ���������ȱ�Ϊ��֪ͨ���ں˶����±� 
	 */
	DWORD dwCode = ::WaitForMultipleObjects(2, hArray, TRUE, 3000);
	printf("%x\n", dwCode);
	MessageBox(0, 0, 0, 0);

	return 0;
}

