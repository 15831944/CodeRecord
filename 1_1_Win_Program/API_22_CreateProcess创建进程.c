/* ************************************
* 创建进程、获取进程相关信息、获取启动参数
**************************************/
/* 头文件　*/
#include <windows.h>
#include <stdio.h>

DWORD CreateChildProcess(LPSTR szChildProcessCmd);

/*************************************
* int main(void)
* 功能	演示进程创建
*
* 参数	未使用
**************************************/
int main()
{	
	CreateChildProcess("Child.exe abc 123");
}
/*************************************
* DWORD CreateChildProcess(LPSTR szChildProcessCmd)
* 功能	演示创建子进程
*
* 参数	LPSTR szChildProcessCmd	启动子进程的命令行
* 返回值	成功返回，失败返回
**************************************/
DWORD CreateChildProcess(LPSTR szChildProcessCmd)
{	
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	// 将启动信息结构清零
	ZeroMemory( &si, sizeof(si) );
	// 设置结构大小，cb属性应为结构的大小
	si.cb = sizeof(si);
	// 将进程信息结构清零
	ZeroMemory( &pi, sizeof(pi) );

	// 创建子进程，并判断是否成功
	if( !CreateProcess( NULL,		// 使用命令行
		szChildProcessCmd,			// 命令行
		NULL,             // 不继承进程句柄
		NULL,             // 不继承线程句柄
		FALSE,            // 不继承句柄
		0,                // 没有创建标志
		NULL,             // 使用父进程环境变量
		NULL,             // 使用父进程目录作为当前目录
		&si,              // STARTUPINFO 结构
		&pi )             // PROCESS_INFORMATION 保存相关信息
		) 
	{
		// 创建失败
		printf( "CreateProcess failed (%d).\n", GetLastError() );
		return 1;
	}
	// 在创建成功后父进程也可直接退出，这里等待子进程执行结束

	// 等待子进程结束
	// 使用到了通过PROCESS_INFORMATION 返回的相关信息，hProcess为子进程句柄
	// 父进程也可以不等待子进程运行完成而直接退出
	WaitForSingleObject( pi.hProcess, INFINITE );
	// 关闭进程句柄和线程句柄
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );
	return 0;
}
