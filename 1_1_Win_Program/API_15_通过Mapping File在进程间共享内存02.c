﻿/* ************************************
* 通过Mapping File在进程间共享内存
**************************************/
#include <windows.h>
#include <stdio.h>
#include <conio.h>
/* 预处理申明*/
#pragma comment (lib, "User32.lib")
#define BUF_SIZE 256
/* 全局变量　*/
TCHAR szName[]=TEXT("SharedFileMappingObject");

/* ************************************
* int main(void)
* 功能	演示文件mapping共享内存，从共享数据中读信息
*
* 参数	无
*
* 返回值	0代表执行完成，代表发生错误
**************************************/
void main()
{
	HANDLE hMapFile;
	LPTSTR pBuf;
	//打开文件mapping
	hMapFile = OpenFileMapping(
		FILE_MAP_ALL_ACCESS,
		FALSE,
		szName); 
	if (hMapFile == NULL) 
	{ 
		printf("OpenFileMapping error: %d.\n",  GetLastError());
		return;
	} 
	//映射
	pBuf = MapViewOfFile(hMapFile,
		FILE_MAP_ALL_ACCESS,
		0,                    
		0,                    
		BUF_SIZE);  
	if (pBuf == NULL) 
	{ 
		printf("MapViewOfFile error %d\n", GetLastError()); 
		return;
	}
	//消息得到的共享数据
	MessageBox(NULL, pBuf, TEXT("Process2"), MB_OK);
	//取消mapping，关闭句柄，返回
	UnmapViewOfFile(pBuf);
	CloseHandle(hMapFile);
}