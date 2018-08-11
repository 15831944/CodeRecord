/* ************************************
弹出消息对话框

MessageBoxA(
    _In_opt_ HWND hWnd,         // 消息框所属的窗口句柄
    _In_opt_ LPCSTR lpText,     // 消息框所显示的消息
    _In_opt_ LPCSTR lpCaption,  // 消息框的标题
    _In_ UINT uType);           // 消息框的类型
**************************************/

/* 预处理　*/
/* 头文件　*/
#include <windows.h>
//连接时使用User32.lib
#pragma comment (lib, "User32.lib")

/* ************************************
* WinMain
* 功能	Windows应用程序示例
**************************************/
int WinMain(
			HINSTANCE hInstance,
			HINSTANCE hPrevInstance,
			LPSTR lpCmdLine,
			int nCmdShow
			)
{
	// 调用API函数 MessageBox
	MessageBox(NULL,
		TEXT("开始学习Windows编程"),
		TEXT("消息对话框"),
		MB_OK);
	return 0;
}