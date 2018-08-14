/* ************************************
* 遍历目录下的文件和子目录
**************************************/

/* 头文件　*/
#include <windows.h>
#include <stdio.h>

/* ************************************
* DWORD EnumerateFileInDrectory(LPSTR szPath)
* 功能	遍历目录下的文件和子目录，将显示文件的
*		文件和文件夹隐藏、加密的属性
* 参数	LPTSTR szPath，为需遍历的路径
* 返回值	0代表执行完成，1代码发生错误
**************************************/
DWORD EnumerateFileInDrectory(LPSTR szPath)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hListFile;
	CHAR szFilePath[MAX_PATH];
	
	//构造代表子目录和文件夹路径的字符串，使用通配符“*”
	lstrcpy(szFilePath, szPath);	
	//注释的代码可以用于查找所有以“.txt结尾”的文件。
	//lstrcat(szFilePath, "\\*.txt");
	lstrcat(szFilePath, "\\*");
	//查找第一个文件/目录，获得查找句柄
	hListFile = FindFirstFile(szFilePath,&FindFileData);
	//判断句柄
	if(hListFile==INVALID_HANDLE_VALUE)
	{
		printf("错误：%d",GetLastError());
		return 1;
	}
	else
	{		
		do
		{
			/*	如果不想显示代表本级目录和上级目录的“.”和“..”，
				可以使用注释部分的代码过滤。
			if(lstrcmp(FindFileData.cFileName,TEXT("."))==0||
				lstrcmp(FindFileData.cFileName,TEXT(".."))==0)
			{
				continue;
			}
			*/
			//打印文件名、目录名
			printf("%s\t\t",FindFileData.cFileName);
			//判断文件属性，加密文件或文件夹
			if(FindFileData.dwFileAttributes&FILE_ATTRIBUTE_ENCRYPTED)
			{
				printf("<加密> ");
			}
			//判断文件属性，隐藏文件或文件夹
			if(FindFileData.dwFileAttributes&FILE_ATTRIBUTE_HIDDEN)
			{
				printf("<隐藏> ");
			}
			//判断文件属性，目录
			if(FindFileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
			{
				printf("<DIR> ");
			}
			//读者可根据文件属性表中的内容自行添加判断文件属性。
			printf("\n");
		}
		while(FindNextFile(hListFile, &FindFileData));
	}
	return 0;
}

/* ************************************
* int main(int argc, PCHAR argv[])
* 功能	调用ListFileInDrectory
*		遍历目录下的文件和子目录
* 参数	argv[1]为需遍历的路径，如果为空则获取
*		当前路径
**************************************/
int main(int argc, PCHAR argv[])
{	
	if(argc == 2)
	{
		EnumerateFileInDrectory(argv[1]);
	}
	else 
	{
		CHAR szCurrentPath[MAX_PATH];
		GetCurrentDirectory(MAX_PATH,szCurrentPath);
		EnumerateFileInDrectory(szCurrentPath);
	}
	return 0;
}