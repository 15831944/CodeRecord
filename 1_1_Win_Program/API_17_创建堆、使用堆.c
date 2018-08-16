/* ************************************
*  堆管理 
*    - 创建堆
*	 - 获得堆句柄并分配内存
**************************************/

/* 头文件　*/
#include <windows.h>
#include <stdio.h>

/*************************************
* DWORD PrintHeapSize(HANDLE hHeap,LPVOID lpMem)
* 功能	获取堆的大小并打印出来
*
* 参数	HANDLE hHeap，堆句柄
*		LPVOID lpMem，内存地址指针
*
* 返回值	0代表执行完成，1代码发生错误。
**************************************/
DWORD PrintHeapSize(HANDLE hHeap,LPVOID lpMem)
{
	SIZE_T dwHeapSize;
	dwHeapSize = HeapSize(hHeap,HEAP_NO_SERIALIZE,lpMem);
	if(dwHeapSize == -1)
	{
		printf("Get HeapSize error :%d",GetLastError());
		return 1;
	}
	printf("内存块大小为:0x%x\n",dwHeapSize);
	return 0;
}

/*************************************
* int main(int argc, PCHAR argv[])
* 功能	演示堆的使用
*
* 参数	argv[1]如果为“-s”那么使用进程堆 
*		argv[1]如果为“-a”那么创建一个可变大小的堆
*		argv[1]如果为其他，那么创建有最大大小的堆。
*
* 2007年10月
*
**************************************/
int main(int argc, PCHAR argv[])
{	
	SYSTEM_INFO si;	//系统信息
	HANDLE hHeap;	//堆句柄
	LPVOID lpMem;	//内存块指针
	LPVOID lpReAlloc;	//内存块大小调整后的指针
	DWORD dwHeapSize;	//堆内存埠大小
	HANDLE hHeaps[24];	//用于保存进程中所有的堆句柄
	DWORD dwHeapNum;	//进程中堆的数量\
	//获取系统信息
	GetSystemInfo(&si);
	//将系统内存分页大小，与内存分配粒度打印出来。
	printf("系统内存页大小: 0x%x\n系统内存分配粒度:0x%x\n",
		si.dwPageSize,si.dwAllocationGranularity);
	//分析输入参数，如果是“-a”创建一个最大为10个分页大小的堆
	if(argc == 2 && 0==lstrcmp(argv[1],"-a"))
	{
		hHeap = HeapCreate(HEAP_NO_SERIALIZE,
			si.dwPageSize,si.dwPageSize*10);
		printf("创建堆,初始化大小为1页,最大为10页\n");
	}
	//如果输入参数为“-s”使用进程初始化时已经存在的堆
	else if(argc == 2 && 0==lstrcmp(argv[1],"-s"))
	{
		hHeap = GetProcessHeap();
		printf("获取系统已经存在的堆\n");
	}
	//如果输入其他，创建一个可增长的堆
	else
	{
		hHeap = HeapCreate(HEAP_NO_SERIALIZE,0,0);
		printf("创建堆,初始化大小为1页,大小可变\n");
	}
	//判断堆是否创建/获取成功
	if(hHeap == NULL)
	{
		printf("创建或获取进程堆错误: %d",GetLastError());
		return 1;
	}
	//获取将打印当前进程中一共有多少个堆，有没有新建堆，值会不同
	dwHeapNum = GetProcessHeaps(24,hHeaps);
	if(dwHeapNum == 0)
	{
		printf("GetProcessHeaps error: %d",GetLastError());
	}
	else
	{
		printf("当前进程一共有%d个堆\n",dwHeapNum);
	}
	//在堆上分析内存，3个页面大小
	lpMem = HeapAlloc(hHeap,HEAP_ZERO_MEMORY,si.dwPageSize*3);
	if(lpMem == NULL)
	{
		printf("HeapAlloc error: %d",GetLastError());
		return 1;
	}
	printf("在堆上成功分配内存,起始地址为:0x%x\n",lpMem);
	//打印当前堆内存块的大小
	PrintHeapSize(hHeap,lpMem);
	//再分配内存，调整内存的大小为11个分页大小，
	//如果使用第一种方法创建堆，这里会出错
	lpReAlloc = HeapReAlloc(hHeap, HEAP_ZERO_MEMORY, lpMem, si.dwPageSize*11);
	if(lpReAlloc == NULL)
	{
		printf("HeapReAlloc error: %d",GetLastError());
		return 1;
	}
	printf("在堆上再分配内存,地址为:0x%x,原地址:0x%x\n",lpReAlloc,lpMem);
	//打印调整大小后的堆内存块大小
	PrintHeapSize(hHeap,lpReAlloc);

	//释放内存
	if(!HeapFree(  hHeap, HEAP_NO_SERIALIZE, lpReAlloc))
	{
		printf("HeapFree error: %d",GetLastError());
		return 1;
	}
	printf("释放内存成功\n");
	//如果新建了堆，销毁堆。
	if(argc != 2 || 0!=lstrcmp(argv[1],"-s"))
	{
		printf("销毁HeapCreate创建的堆\n");
		if(!HeapDestroy(hHeap))
		{
			printf("HeapDestroy error: %d",GetLastError());
			return 1;
		}
		printf("销毁堆成功\n");	
	}
	return 0;
}