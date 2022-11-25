#pragma   comment(linker,"/subsystem:\"windows\"  /entry:\"mainCRTStartup\"") // 隐藏控制台
#include<stdio.h>
#include<Windows.h>


//查找指定窗口
void test01()
{
  // MAX_PATH 宏 260
	TCHAR szTitle[MAX_PATH] = { 0 };

	//参数1 ClassName  参数2 窗口名称（标题名称）
	HWND hwnd = ::FindWindow(TEXT("#32770"), TEXT("飞鸽传书  IP Messenger (IPMsg)"));

	if (hwnd != NULL)
	{
		//修改窗口标题
		//参数： 1 句柄   | 2 新的标题或控件文本。
		::SetWindowText(hwnd, TEXT("新的窗口"));
	}
	else
	{
		//参数： 1 句柄 | 2 要显示的内容 | 3 对话框标题| 4 对话框内容和行为
		::MessageBox(NULL, TEXT("窗口没有找到"), TEXT("[ERROR]"), MB_OK); //MB_OK 消息框包含一个按钮：确定
	}

}

//窗口控制
void test02()
{
	TCHAR siTitle[MAX_PATH] = { 0 };
	HWND hwnd = ::FindWindow(TEXT("#32770"), TEXT("飞鸽传书  IP Messenger (IPMsg)"));

	if (hwnd != NULL)
	{
		//下面是使用typedef直接定义的函数指针
		typedef void (WINAPI* PSWITCHTOTHISWINDOW)(HWND, BOOL);
 
      // 上面函数指针定义好了之后，相当于下面可以直接使用带着函数类型的指针
      // PSWITCHTOTHISWINDOW， 将这函数指针直接实例化
		PSWITCHTOTHISWINDOW SwitchToThisWindow;
 
		//通过LordLibrary获取user32.dll的模块句柄
		HMODULE hUser32 = LoadLibrary("user32.dll"); // HMODULE 应用程序载入的模块

		// GetProcAddress 从指定的动态链接库 （DLL） 中检索导出的函数（也称为过程）或变量的地址。
		// 参数 1 包含函变量的DLL模块的句柄 |  参数2 函数或变量名称，或函数的序号值 
		// 使用GetproAddess 获取需要的函数地址，然后将这个地址给函数指针
		SwitchToThisWindow = (PSWITCHTOTHISWINDOW)GetProcAddress(hUser32, "SwitchToThisWindow");

		Sleep(2000);
		//切换窗口
		//上面把 user32.dll 的切换窗口函数地址拿出来了，现在调用函数指针切换窗口
		SwitchToThisWindow(hwnd, true);
 
		Sleep(2000);
		//关闭窗口
		::SendMessage(hwnd, WM_CLOSE, 0, 0);
	}
	else
	{
		::MessageBox(NULL, TEXT("窗口没有找到"), TEXT("[ERROR]"), MB_OK);
	}
}


//查找子窗口
void test03()
{
	
	TCHAR szTitle[MAX_PATH] = { 0 };

	HWND hwnd = ::FindWindow(TEXT("#32770"), TEXT("飞鸽传书  IP Messenger (IPMsg)"));
	if (hwnd != NULL)
	{
		//查找子窗口	第三个参数是要查找的子窗口的类名，第四个参数是要查找的子窗口的标题						
		HWND hEdit = FindWindowEx(hwnd, NULL, "RichEdit20W", "");
		//上述第三个参数是通过Spy++找到的类，不能想当然的写Edit，查找到第四个参数标题是空

		//下面的操作就是设置上面找到的RichEdit20W，设置她的标题，因为未操作之前标题是空
		//设置标题		 使用工具Spy++进行验证测试					
		::SetWindowText(hEdit, "文本框新的标题");
		//修改内容							
		::SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)"新的内容");
	}
	else
	{
		::MessageBox(NULL, TEXT("窗口没有找到"), TEXT("[ERROR]"), MB_OK);
	}

}

//查找子窗口 通过控件 id
void test04()
{

	TCHAR szTitle[MAX_PATH] = { 0 };
	HWND hwnd = ::FindWindow(TEXT("#32770"), TEXT("飞鸽传书  IP Messenger (IPMsg)"));
	if (hwnd != NULL)
	{
		//获取子窗口的句柄
		HWND hEdit = ::GetDlgItem(hwnd, 0x3E9);
		//获取内容
		::SendMessage(hEdit, WM_GETTEXT, MAX_PATH, (LPARAM)szTitle);

		//设置内容
		::SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)"新设置的内容");
	}
	else
	{
		::MessageBox(NULL, TEXT("窗口没有找到"), TEXT("Errors"), MB_OK);
	}
}

//枚举子窗口控件
BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam)
{
	TCHAR szTitle[MAX_PATH] = { 0 };
	//获取窗口文本或控件文本
	::GetWindowText(hWnd, szTitle, MAX_PATH);
	MessageBox(NULL, szTitle, "[子窗口]", MB_OK);
	return true;
}

VOID EnumChildWindow()
{
	TCHAR szTitle[MAX_PATH] = { 0 };
	HWND hWnd = ::FindWindow(TEXT("#32770"), TEXT("飞鸽传书  IP Messenger (IPMsg)"));
	if (hWnd != NULL)
	{
		::EnumChildWindows(hWnd, EnumChildProc, 0);
	}
	else
	{
		::MessageBox(NULL, TEXT("窗口没有找到"), TEXT("[ERROR]"), MB_OK);
	}
}


//枚举所有打开窗口
BOOL CALLBACK EnumOpenWindowProc(HWND hWnd, LPARAM lParam)
{
	TCHAR szTitle[MAX_PATH] = { 0 };
	::GetWindowText(hWnd, szTitle, MAX_PATH);
	MessageBox(NULL, szTitle, "[窗口]", MB_OK);
	if (strcmp(szTitle, "飞鸽传书  IP Messenger (IPMsg)") == 0)
	{
		MessageBox(NULL, szTitle, "[窗口]", MB_OK);
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
	
	//枚举子窗口
	EnumChildWindow();

	//枚举所有打开窗口
	EnumOpenWindows();

	return 0;
}


//模拟鼠标单机
VOID TestMouseClick()
{
	TCHAR szTitle[MAX_PATH] = { 0 };
	//RECT 结构通过其左上角和右下角的坐标定义矩形。
	RECT r;
	HWND hwnd = ::FindWindow(TEXT("#32770"), TEXT("飞鸽传书  IP Messenger (IPMsg)"));
	if (hwnd != NULL)
	{
		HWND hButton = FindWindowEx(hwnd, NULL, "Button", "刷新(&R)");

		//获取窗口坐标
		::GetWindowRect(hButton, &r);

		printf("%d %d\n", r.left, r.top); // r.left 左上角 x左边   r.left 左上角y坐标

		//设置鼠标的位置
		::SetCursorPos(r.left + 5, r.top + 5); //直接获取的坐标在 button 左上角 所以 加上偏移
		Sleep(3000);

		//鼠标左键单机
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);  //点击左键  MOUSEEVENTF_LEFTDOWN 左键已关闭
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);	//松开左键  MOUSEEVENTF_LEFTUP	左键已打开
	}
	else
	{
		::MessageBox(NULL, TEXT("窗口没有找到"), TEXT("[ERROR]"), MB_OK);
	}

}


//模拟键盘
VOID Testmnkeyboard()
{
	TCHAR szTiTle[MAX_PATH] = { 0 };
	RECT r;
	HWND hwnd = ::FindWindow(TEXT("#32770"), TEXT("飞鸽传书  IP Messenger (IPMsg)"));
	if (hwnd != NULL)
	{
		//HWND hButton = FindWindowEx(hwnd, NULL, "Button", "刷新(&R)");
		HWND hEdit = ::GetDlgItem(hwnd, 0x3E9);

		/// 获取窗口坐标
		::GetWindowRect(hEdit, &r);

		//获取鼠标的位置
		::SetCursorPos(r.left + 1, r.top + 1);
		Sleep(3000); //这里尽可能时间稍微常一点 避免翻译器执行移动鼠标 跟自己 没有松开鼠标而出现冲突

		//鼠标左键单击
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);  //点击左键  MOUSEEVENTF_LEFTDOWN 左键已关闭
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);	//松开左键  MOUSEEVENTF_LEFTUP	左键已打开

		//模拟键盘
		keybd_event(97, 0, 0, 0);
		keybd_event(97, 0, KEYEVENTF_KEYUP, 0);
		Sleep(1000);
		keybd_event(66, 0, 0, 0);
		keybd_event(66, 0, KEYEVENTF_KEYUP, 0); // KEYEVENTF_KEYUP 如果指定，则释放密钥。如果未指定，则键被按下
		Sleep(1000);
		keybd_event(16, 0, 0, 0);
		keybd_event(67, 0, 0, 0);
		keybd_event(67, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(16, 0, KEYEVENTF_KEYUP, 0);
	}
	else
	{
		::MessageBox(NULL, TEXT("窗口没有找到"), TEXT("[ERROR]"), MB_OK);
	}

}



int main()
{
	//TestMouseClick();

	Testmnkeyboard();

	return 0;
}
