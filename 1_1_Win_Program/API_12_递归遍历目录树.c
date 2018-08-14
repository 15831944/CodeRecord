/* ************************************
* 递归遍历目录树
**************************************/

/* 头文件　*/
#include <windows.h>
#include <stdio.h>

/* 预处理申明 */
#pragma comment (lib, "User32.lib")

/* 函数申明　*/
DWORD ListAllFileInDrectory(LPSTR szPath);

/* 全局变量　*/
//记录所有的文件和目录数
DWORD dwTotalFileNum = 0;


/* ************************************
* DWORD ListAllFileInDrectory(LPSTR szPath)
* 功能	遍历目录及所有子目录，打印路径
*
* 参数	LPTSTR szPath，为需遍历的目录
*
* 返回值	0代表执行完成，1代码发生错误
**************************************/
DWORD ListAllFileInDrectory(LPSTR szPath)
{
	CHAR szFilePath[MAX_PATH];

	WIN32_FIND_DATA FindFileData;
	HANDLE hListFile;
	CHAR szFullPath[MAX_PATH];

	//构造代表子目录和文件夹路径的字符串，使用通配符“*”
	lstrcpy(szFilePath, szPath);
	lstrcat(szFilePath, "\\*");
	//查找第一个文件/目录，获得查找句柄
	hListFile = FindFirstFile(szFilePath,&FindFileData);

	if(hListFile==INVALID_HANDLE_VALUE)
	{
		printf("错误：%d",GetLastError());
		return 1;
	}
	else
	{		
		do
		{
			//	过滤“.”和“..”，不需要遍历
			if(lstrcmp(FindFileData.cFileName,TEXT("."))==0||
				lstrcmp(FindFileData.cFileName,TEXT(".."))==0)
			{
				continue;
			}
			//构造成全路径
			wsprintf(szFullPath,"%s\\%s",
				szPath,FindFileData.cFileName);
			dwTotalFileNum++;
			//打印
			printf("\n%d\t%s\t",dwTotalFileNum,szFullPath);

			//如果是目录，则递归调用，列举下级目录
			if(FindFileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
			{
				printf("<DIR>");
				ListAllFileInDrectory(szFullPath);
			}			
		}
		while(FindNextFile(hListFile, &FindFileData));
	}
	return 0;
}


/* ************************************
* int main(int argc, PCHAR argv[])
* 功能	调用ListAllFileInDrectory
*		遍历目录下的文件和子目录
*
* 参数	argv[1]为需遍历的路径，如果为空则获取
*		当前路径
*
* 2007年10月
*
**************************************/
int main(int argc, PCHAR argv[])
{	
	if(argc == 2)
	{
		ListAllFileInDrectory(argv[1]);
	}
	else 
	{
		CHAR szCurrentPath[MAX_PATH];
		GetCurrentDirectory(MAX_PATH,szCurrentPath);
		ListAllFileInDrectory(szCurrentPath);
	}
	return 0;
}