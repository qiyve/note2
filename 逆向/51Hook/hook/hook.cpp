#include<Windows.h>
#include<iostream>
typedef BOOL(*InstallHook)();
typedef BOOL(*UnInstallHook)();
int main()
{
	HMODULE hmodule = LoadLibraryA("hookDll.dll");
	InstallHook myInstallHook = (InstallHook)GetProcAddress(hmodule,"InstallHook");
	UnInstallHook myUnInstallHook = (UnInstallHook)GetProcAddress(hmodule, "UnInstallHook");

	if (myInstallHook())
	{
		printf("Hook³É¹¦£¡\n");
	}
	system("pause");
	myUnInstallHook();
	return 0;
}