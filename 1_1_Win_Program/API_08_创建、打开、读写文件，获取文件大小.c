/* ************************************
* 创建、打开、读写文件，获取文件大小
**************************************/

/* 头文件　*/
#include <windows.h>
#include <stdio.h>

/* ************************************
* DWORD ReadFileContent(LPSTR szFilePath)
* 功能	获取文件大小
*		读取文件内容，并以16进制的形式打印出来
* 参数	LPSTR szFilePath
*		文件路径
**************************************/
DWORD ReadFileContent(LPSTR szFilePath)
{
	//文件大小
	HANDLE hFileRead;
	//保存文件大小
	LARGE_INTEGER liFileSize;
	//成功读取的文件数据大小
	DWORD dwReadedSize;
	//累加计算已经读取数据的大小
	LONGLONG liTotalRead = 0;
	//文件数据缓存
	BYTE lpFileDataBuffer[32];

	//打开已经存在的文件，读取内容。	
	hFileRead = CreateFile(szFilePath,// 要打开的文件名
		GENERIC_READ,			   // 以读方式打开
		FILE_SHARE_READ,           // 可共享读
		NULL,                      // 默认安全设置
		OPEN_EXISTING,             // 只打开已经存在的文件
		FILE_ATTRIBUTE_NORMAL,     // 常规文件属性
		NULL);                     // 无模板

	//打开文件是否成功。
	if(hFileRead==INVALID_HANDLE_VALUE)
	{
		printf("打开文件失败：%d",GetLastError());
	}

	if(!GetFileSizeEx(hFileRead,&liFileSize))
	{
		printf("获取文件大小失败：%d",GetLastError());
	}
	else
	{
		printf("文件大小为：%d\n",liFileSize.QuadPart);
	}

	//循环读取并打印文件内容
	while(TRUE)
	{
		DWORD i;

		if(!ReadFile(hFileRead,	//读文件的句柄
			lpFileDataBuffer,	//存储读取的文件内容
			32,					//读的大小（字节）
			&dwReadedSize,		//实际读取的大小
			NULL))				//不使用Overlapped
		{
			printf("读文件错误：%d\n",GetLastError());
			break;
		}
		printf("读取了%d字节，文件内容是：",dwReadedSize);

		for(i=0; i<dwReadedSize; i++)
		{

			printf("0x%x ",lpFileDataBuffer[i]);

		}
		printf("\n");

		liTotalRead += dwReadedSize;
		if(liTotalRead == liFileSize.QuadPart)
		{
			printf("读文件结束\n");
			break;
		}
	}
	CloseHandle(hFileRead);
	return 0;
}

/* ************************************
*  SaveDataToFile
* 功能	将数据存储到文件末尾
* 参数	LPSTR szFilePath	文件路径
*		LPVOID lpData		需存储的数据
*		DWORD dwDataSize	数据大小（字节）
**************************************/
DWORD SaveDataToFile(
					 LPSTR szFilePath,
					 LPVOID lpData,
					 DWORD dwDataSize)
{
	//文件句柄
	HANDLE hFileWrite;
	//成功写入的数据大小
	DWORD dwWritedDateSize;

	//打开已经存在的文件，读取内容。	
	hFileWrite = CreateFile(szFilePath,	// 要打开的文件名
		GENERIC_WRITE,			// 以写方式打开
		0,						// 可共享读
		NULL,					// 默认安全设置
		OPEN_ALWAYS,			// 打开已经存在的文件，没用则创建
		FILE_ATTRIBUTE_NORMAL,	// 常规文件属性
		NULL);					// 无模板
	
	//判断是否打开成功
	if(hFileWrite==INVALID_HANDLE_VALUE)
	{
		printf("打开文件失败：%d\n",GetLastError());
	}

	//设置文件指针到文件尾
	SetFilePointer(hFileWrite,0,0,FILE_END);

	//将数据写入文件
	if(!WriteFile(hFileWrite,lpData,dwDataSize,&dwWritedDateSize,NULL))
	{
		printf("写文件失败：%d\n",GetLastError());
	}
	else
	{
		printf("写文件成功，写入%d字节。\n",dwWritedDateSize);
	}
	CloseHandle(hFileWrite);
	return 0;
}

/* ************************************
* int main(void)
* 功能	演示使用SaveDataToFile和ReadFileContent函数
**************************************/
int main(void)
{
	LPSTR szFileData = "这是一个例子";
	SaveDataToFile("D:\\show.txt",szFileData,lstrlen(szFileData));
	ReadFileContent("D:\\show.txt");
	return 0;
}