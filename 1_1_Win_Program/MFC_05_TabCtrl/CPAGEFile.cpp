// CPAGEFile.cpp: 实现文件
//

#include "stdafx.h"
#include "MFC_05_TabCtrl.h"
#include "CPAGEFile.h"
#include "afxdialogex.h"


// CPAGEFile 对话框

IMPLEMENT_DYNAMIC(CPAGEFile, CDialogEx)

CPAGEFile::CPAGEFile(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PAGE_FILE, pParent)
{

}

CPAGEFile::~CPAGEFile()
{
}

void CPAGEFile::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPAGEFile, CDialogEx)
END_MESSAGE_MAP()


// CPAGEFile 消息处理程序
