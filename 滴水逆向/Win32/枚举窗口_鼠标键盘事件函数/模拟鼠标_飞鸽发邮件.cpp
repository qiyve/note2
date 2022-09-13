#include<stdio.h>
#include<Windows.h>


//设置鼠标位置

//通过程序启动QQ,实现自动登录.		
void Open_ipmsg()
{
	//1、CreateProcess创建进程
	TCHAR szCmdline[] = TEXT("D:\\ipmsg.exe");
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi;

	BOOL res = CreateProcess(
		NULL,			 // 应用程序名称
		szCmdline,		 // 命令行字符串      
		NULL,			 // 进程的安全属性 
		NULL,			 // 线程的安全属性 
		FALSE,		 	 // 是否继承父进程的属性  
		CREATE_NEW_CONSOLE,	// 创建标志  
		NULL,			// 指向新的环境块的指针 
		NULL,			// 指向当前目录名的指针 
		&si,			// 传递给新进程的信息
		&pi				// 新进程返回的信息     
	);
	Sleep(4000);//等待ipmsg.exe打开


	//2、遍历所有打开窗口，等待。。。
	TCHAR szTitle[MAX_PATH] = { 0 };
	HWND hwnd = ::FindWindow(TEXT("#32770"), TEXT("飞鸽传书  IP Messenger (IPMsg)"));

	if (hwnd != NULL)
	{
		//将QQ 置与前台  定义函数指针
		typedef void (WINAPI* PSWITCHTOTHISWINDOW)(HWND, BOOL);
		//函数指针实例化
		PSWITCHTOTHISWINDOW SwichToThisWindow;

		//通过LoadLibrary 获取 user32.dll 的模块句柄
		HMODULE hUser32 = LoadLibrary("user32.dll");

		// 使用GetproAddess 获取需要的函数地址，然后将这个地址给函数指针
		SwichToThisWindow = (PSWITCHTOTHISWINDOW)GetProcAddress(hUser32, "SwitchToThisWindow");

		Sleep(2000);
		//切换窗口 
		SwichToThisWindow(hwnd, true);

		//3、设置鼠标位置，点击
		RECT r;
		HWND hEdit = GetDlgItem(hwnd, 0x3E9);

		//获取窗口坐标地址
		::GetWindowRect(hEdit, &r);

		//获取鼠标的位置
		::SetCursorPos(r.left + 1, r.top + 1);
		Sleep(3000);

		//鼠标点击该区域
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

		//模拟键盘输入 其 账号 密码
		keybd_event(49, 0, 0, 0);			// 1
		keybd_event(49, 0, KEYEVENTF_KEYUP, 0);	 // 输入
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
		keybd_event(13, KEYEVENTF_KEYUP, 0, 0); // 回车  换行

		keybd_event(16, 0, 0, 0);  // A
		keybd_event(65, 0, 0, 0);  // Shift
		keybd_event(65, 0, KEYEVENTF_KEYUP, 0); // 输入
		keybd_event(16, 0, KEYEVENTF_KEYUP, 0);
		Sleep(1000);
		keybd_event(66, 0, 0, 0);  // b
		keybd_event(66, 0, KEYEVENTF_KEYUP, 0);
		Sleep(1000);
		keybd_event(67, 0, 0, 0);  // c
		keybd_event(67, 0, KEYEVENTF_KEYUP, 0);

		//点击发送
		HWND Button = FindWindowEx(hwnd, NULL, TEXT("Button"), TEXT("发送(&S)"));
		//获取去按钮位置
		::GetWindowRect(Button, &r);
		//获取鼠标位置
		::SetCursorPos(r.left + 5, r.top + 5);

		//鼠标点击该区域
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

		//点击发送人
		HWND preson = FindWindowEx(hwnd, NULL, TEXT("SysListView32"), TEXT("List1"));
		//获取去按钮位置
		::GetWindowRect(preson, &r);
		//获取鼠标位置
		::SetCursorPos(r.left + 5, r.top + 10);

		//鼠标点击该区域
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	}
	else
	{
		::MessageBox(NULL, TEXT("未找到窗口"), TEXT("[ERROR]"), MB_OK);
	}
}

int main()
{
	Open_ipmsg();

	return 0;
}