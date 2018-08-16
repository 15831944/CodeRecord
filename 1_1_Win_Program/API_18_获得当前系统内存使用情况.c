/* ************************************
*  获得当前系统内存使用情况
**************************************/

/* 头文件　*/
#include <windows.h>
#include <stdio.h>

/* 常量定义 */
#define MEM_BLOCK_MAX_SIZE 32

/*************************************
* BOOL ShowMemContent(LPVOID lpMem,SIZE_T dwSize)
* 功能	显示内存中的内容
*
* 参数	LPVOID lpMem 需要显示的内存指针
*		SIZE_T dwSize 大小
*
* 返回值 BOOL 如果数据过大可能溢出，则返回FALSE。 
**************************************/
BOOL ShowMemContent(LPVOID lpMem,SIZE_T dwSize)
{
	BYTE lpShow[MEM_BLOCK_MAX_SIZE];
	INT i=0;
	//防止栈溢出
	if(dwSize>MEM_BLOCK_MAX_SIZE)
	{
		printf("over-flow");
		return FALSE;
	}
	//复制到数组
	CopyMemory((LPVOID)lpShow,lpMem,dwSize);
	//显示
	for(; i<dwSize; i++)
	{		
		printf("%.2X ",lpShow[i]);
		if(!((i+1)%16))
		{
			printf("\n");
		}		
	}
	printf("\n");
	return TRUE;
}

/*************************************
* int main(void)
* 功能	获取内存使用情况
*
* 参数	未使用
**************************************/
int main(void)
{	
	HANDLE hHeap = GetProcessHeap();
	LPVOID lpSrc;
	LPVOID lpDis;

	//分配内存
	lpSrc = HeapAlloc(hHeap,0,MEM_BLOCK_MAX_SIZE);
	lpDis = HeapAlloc(hHeap,0,MEM_BLOCK_MAX_SIZE);
	//显示新分配的内存
	printf("HeapAlloc 分配但不清零：\n");
	ShowMemContent(lpDis, MEM_BLOCK_MAX_SIZE);	
	//将内存清零并显示
	ZeroMemory(lpDis,MEM_BLOCK_MAX_SIZE);
	printf("ZeroMemory 清零：\n");
	ShowMemContent(lpDis, MEM_BLOCK_MAX_SIZE);
	//使用0xBB填充全部内存
	FillMemory(lpSrc,MEM_BLOCK_MAX_SIZE,0xBB);
	//将内存块的前半部分使用0xAA填充
	FillMemory(lpSrc,MEM_BLOCK_MAX_SIZE/2,0xAA);
	CopyMemory(lpDis,lpSrc,MEM_BLOCK_MAX_SIZE);
	printf("FillMemory 有规律的填充内存：\n");
	ShowMemContent(lpDis,MEM_BLOCK_MAX_SIZE);

	//释放内存
	HeapFree(hHeap,0,lpSrc);
	HeapFree(hHeap,0,lpDis);
	return 0;

}