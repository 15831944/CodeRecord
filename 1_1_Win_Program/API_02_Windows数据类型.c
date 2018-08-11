/* ************************************
* 常用的Windows数据类型
* DWORD、LPSTR、CHAR、INT
**************************************/

/* 头文件　*/
#include <windows.h>
#include <stdio.h>

int WINAPI WinMain(
            HINSTANCE hInstance,
            HINSTANCE hPrevInstance,
            LPSTR lpCmdLine,
            int nCmdShow
            )
{
    //定义字符串
    LPSTR szString = "Windows data type, string.";
    //定义字符数组
    CHAR lpString[120];//要大于szString的长度
    //定义DWORD类型的数据
    DWORD dwMax = 0xFFFFFFFF;
    DWORD dwOne = 0x1;
    //定义INT类型的数据
    INT iMax = 0xFFFFFFFF;
    INT iOne = 0x1;
    
    //显示字符串
    MessageBox(NULL,szString,"LPSTR",MB_OK);
    //复制内存，将字符串复制到数组中（包括NULL结束符）
    CopyMemory(lpString, szString,lstrlen(szString)+1);
    //显示复制的字符串
    MessageBox(NULL,lpString,"CHAR[]",MB_OK);

    //比较DWORD并显示结果
    if(dwMax>dwOne)
    {
        MessageBox(NULL,"DWORD类型的数据 OxFFFFFFFF > 0x1","DWORD",MB_OK);
    }
    //比较INT并显示结果
    if(iMax<iOne)
    {
        MessageBox(NULL,"INT类型的数据 OxFFFFFFFF < 0x1","INT",MB_OK);
    }
    return 0;
}