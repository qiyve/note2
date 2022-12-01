#include"hookmain.h"

int WINAPI hookMessageBoxW(
	HWND    hWnd,
	LPCWSTR lpText,
	LPCWSTR lpCaption,
	UINT    uType
	)
{
	UnstallHook();
	DWORD result = MessageBoxW(hWnd, L"IAThook", L"提示", MB_OK);
	InstallHook();
	return result;
	//DWORD result = MessageBoxA(hWnd, "IAThook", "提示", MB_OK);
	//return result;
}

//安装钩子
DWORD InstallHook()
{
	DWORD dwOldProtect = 0;
	//修改权限
	VirtualProtect(g_iatAddr, 4, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	*g_iatAddr = (DWORD)hookMessageBoxW;
	VirtualProtect(g_iatAddr, 4, dwOldProtect, &dwOldProtect);
	MessageBoxA(0, "HOOk成功", "提示", MB_OK);
	return TRUE;
}

//卸载钩子
DWORD UnstallHook()
{
	DWORD dwOldProtect = 0;
	VirtualProtect(g_iatAddr, 4, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	*g_iatAddr = (DWORD)g_UnhookFuncAddr;
	VirtualProtect(g_iatAddr, 4, dwOldProtect, &dwOldProtect);
	return TRUE;
}


DWORD* GetIatAddr(char* dllname, char*funname)
{
	HMODULE hModule = GetModuleHandle(0);
	DWORD dwhModule = (DWORD)hModule;

	PIMAGE_DOS_HEADER pdosHeader = (PIMAGE_DOS_HEADER)dwhModule;
	PIMAGE_NT_HEADERS pNtHeader = (PIMAGE_NT_HEADERS)(pdosHeader->e_lfanew + dwhModule);
	PIMAGE_OPTIONAL_HEADER pOptionHeader = &(pNtHeader->OptionalHeader);
	//数据目录表
	IMAGE_DATA_DIRECTORY dataDirectory = pOptionHeader->DataDirectory[1];
	//导入表
	PIMAGE_IMPORT_DESCRIPTOR pImprotTable =
		(PIMAGE_IMPORT_DESCRIPTOR)(dataDirectory.VirtualAddress +dwhModule);

	while (pImprotTable->Name)
	{
		char* dllName = (char*)(pImprotTable->Name + dwhModule);
		if (_stricmp(dllName, dllname) == 0) //dll名称不区分大小写 
		{
			//获取导入名称表
			PIMAGE_THUNK_DATA pINT = (PIMAGE_THUNK_DATA)
				(pImprotTable->OriginalFirstThunk + dwhModule);
			//获取导入地址表
			PIMAGE_THUNK_DATA pIAT = (PIMAGE_THUNK_DATA)
				(pImprotTable->OriginalFirstThunk + dwhModule);

			while (pINT->u1.Function)
			{
				if ((pINT->u1.Ordinal & 0x80000000) == 0) //名称导入
				{
					PIMAGE_IMPORT_BY_NAME pImportName = 
						(PIMAGE_IMPORT_BY_NAME)(pINT->u1.Ordinal + dwhModule);

					if (strcmp(pImportName->Name, funname)==0)
					{
						return (DWORD*)pIAT;
					}
				}
				pINT++;
				pIAT++;
			}
		}
		pImprotTable++;
	}
	return NULL;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwCallReason, LPVOID lpReserved)
{
	//进程创建时
	if (dwCallReason == DLL_PROCESS_ATTACH)
	{
		MessageBoxA(0, "DLL加载", "提示", MB_OK);
		g_iatAddr = GetIatAddr("user32.dll", "MessageBoxW");
		g_UnhookFuncAddr = (DWORD*)(*g_iatAddr);
		BOOL result = InstallHook();
		MessageBoxA(0, "DLL加载完毕", "提示", MB_OK);
	}
	else if (dwCallReason == DLL_PROCESS_DETACH)
	{
		UnstallHook();
	}
	return TRUE;
}