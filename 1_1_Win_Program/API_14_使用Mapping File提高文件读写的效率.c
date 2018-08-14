/* ************************************
* 使用Mapping File提高文件读写的效率
**************************************/

/* 头文件　*/
#include <windows.h>
#include <stdio.h>
/* 预处理申明　*/
#define BUFFSIZE 1024					// 内存大小
#define FILE_MAP_START 0x28804			// 文件映射的起始的位置
/* 全局变量　*/
LPTSTR lpcTheFile = TEXT("test.dat");	// 文件名

/* ************************************
* int main(void)
* 功能	演示使用文件mapping
*
* 参数	无
*
* 返回值	0代表执行完成，1代表发生错误
**************************************/
int main(void)
{
	HANDLE hMapFile;      // 文件内存映射区域的句柄
	HANDLE hFile;         // 文件的句柄
	DWORD dBytesWritten;  // 写入的字节数
	DWORD dwFileSize;     // 文件大小
	DWORD dwFileMapSize;  // 文件映射的大小
	DWORD dwMapViewSize;  // 视图（View）的大小
	DWORD dwFileMapStart; // 文件映射视图的起始位置
	DWORD dwSysGran;      // 系统内存分配的粒度
	SYSTEM_INFO SysInfo;  // 系统信息
	LPVOID lpMapAddress;  // 内在映射区域的起始位置
	PCHAR pData;			// 数据
	INT i;                // 循环变量
	INT iData;
	INT iViewDelta;
	BYTE cMapBuffer[32];  // 存储从mapping中计出的数据

	// 创建一个文件
	hFile = CreateFile(lpcTheFile, 
		GENERIC_READ | GENERIC_WRITE,
		0, 
		NULL,
		CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);
	//判断文件是否创建成功
	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("CreateFile error\n",GetLastError);
		return 1;
	}
	// 依次写入整数，一共写入65535个整数
	// 在32位平台下，大小为65535*32
	for (i=0; i<65535; i++) 
	{
		WriteFile (hFile, &i, sizeof (i), &dBytesWritten, NULL);
	}
	// 查看写入完成后的文件大小
	dwFileSize = GetFileSize(hFile,  NULL);
	printf("文件大小: %d\n", dwFileSize);

	//获取系统信息，内存分配粒度
	//获取分配粒度，进行下面的几个计算，
	//目的是为了映射的数据与系统内存分配粒度对齐，提高内存访问效率
	GetSystemInfo(&SysInfo);
	dwSysGran = SysInfo.dwAllocationGranularity;

	//计算mapping的起始位置
	dwFileMapStart = (FILE_MAP_START / dwSysGran) * dwSysGran;
	// 计算mapping view的大小
	dwMapViewSize = (FILE_MAP_START % dwSysGran) + BUFFSIZE;
	// 计算mapping的大小
	dwFileMapSize = FILE_MAP_START + BUFFSIZE;
	// 计算需要读取的数据的偏移
	iViewDelta = FILE_MAP_START - dwFileMapStart;

	// 创建File mapping
	hMapFile = CreateFileMapping( hFile,          // 需要映射的文件的句柄
		NULL,           // 安全选项：默认
		PAGE_READWRITE, // 可读，可写
		0,              // mapping对象的大小，高位
		dwFileMapSize,  // mapping对象的大小，低位
		NULL);          // mapping对象的名字
	if (hMapFile == NULL) 
	{
		printf("CreateFileMapping error: %d\n", GetLastError() );
		return 1;
	}

	// 映射view
	lpMapAddress = MapViewOfFile(hMapFile,            // mapping对象的句柄
		FILE_MAP_ALL_ACCESS, // 可读，可写
		0,                   // 映射的文件偏移，高32位
		dwFileMapStart,      // 映射的文件偏移，低32位
		dwMapViewSize);      // 映射到View的数据大小
	if (lpMapAddress == NULL) 
	{
		printf("MapViewOfFile error: %d\n", GetLastError());
		return 1;
	}

	printf ("文件map view相对于文件的起始位置： 0x%x\n",
		dwFileMapStart);
	printf ("文件map view的大小：0x%x\n", 	dwMapViewSize);
	printf ("文件mapping对象的大小：0x%x\n", dwFileMapSize);
	printf ("从相对于map view 0x%x 字节的位置读取数据，", iViewDelta);

	// 将指向数据的指针偏移，到达我们关心的地方
	pData = (PCHAR) lpMapAddress + iViewDelta;
	// 读取数据，赋值给变量
	iData = *(PINT)pData;
	// 显示读取的数据
	printf ("为：0x%.8x\n", iData);

	// 从mapping中复制数据，32个字节，并打印
	CopyMemory(cMapBuffer,lpMapAddress,32);
	printf("lpMapAddress起始的32字节是：");
	for(i=0; i<32; i++)
	{
		printf("0x%.2x ",cMapBuffer[i]);
	}
	// 将mapping的前32个字节用0xff填充
	FillMemory(lpMapAddress,32,(BYTE)0xff);
	// 将映射的数据写回到硬盘上
	FlushViewOfFile(lpMapAddress,dwMapViewSize);
	printf("\n已经将lpMapAddress开始的32字节使用0xff填充。\n");

	// 关闭mapping对象
	if(!CloseHandle(hMapFile)) 
	{
		printf("\nclosing the mapping object error %d!",
			GetLastError());
	}
	//关闭文件
	if(!CloseHandle(hFile)) 
	{
		printf("\nError %ld occurred closing the file!",
			GetLastError());
	}

	return 0;
}