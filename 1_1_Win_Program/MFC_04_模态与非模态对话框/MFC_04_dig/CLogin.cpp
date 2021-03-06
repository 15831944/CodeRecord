// CLogin.cpp: 实现文件
//

#include "stdafx.h"
#include "MFC_04_dig.h"
#include "CLogin.h"
#include "afxdialogex.h"


// CLogin 对话框

IMPLEMENT_DYNAMIC(CLogin, CDialogEx)

CLogin::CLogin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOGIN, pParent)
	, m_szId(_T(""))
	, m_szPwd(_T(""))
	, m_bAutoLogin(FALSE)
	, m_bSavePwd(FALSE)
{

}

CLogin::~CLogin()
{
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_szId);
	DDX_Text(pDX, IDC_EDIT2, m_szPwd);
	DDX_Check(pDX, IDC_CHECK2, m_bAutoLogin);
	DDX_Check(pDX, IDC_CHECK1, m_bSavePwd);
}


BEGIN_MESSAGE_MAP(CLogin, CDialogEx)
END_MESSAGE_MAP()


// CLogin 消息处理程序
