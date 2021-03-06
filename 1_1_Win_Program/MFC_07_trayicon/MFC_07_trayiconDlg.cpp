
// MFC_07_trayiconDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFC_07_trayicon.h"
#include "MFC_07_trayiconDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define		WM_ICON_NOTIFY	WM_USER+100
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFC07trayiconDlg 对话框



CMFC07trayiconDlg::CMFC07trayiconDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_07_TRAYICON_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC07trayiconDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC07trayiconDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_ICON_NOTIFY, OnTrayNotification)
	ON_COMMAND(ID_TRAY_RESTORE, &CMFC07trayiconDlg::OnTrayRestore)
	ON_COMMAND(ID_TRAY_EXIT, &CMFC07trayiconDlg::OnTrayExit)
END_MESSAGE_MAP()


// CMFC07trayiconDlg 消息处理程序

BOOL CMFC07trayiconDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
		// TODO: 在此添加额外的初始化代码
	NOTIFYICONDATA m_tnid;

	m_tnid.cbSize = sizeof(NOTIFYICONDATA);//设置结构大小// 
	m_tnid.hWnd = this->m_hWnd;//设置图标对应的窗口 
	m_tnid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;//图标属性 
	m_tnid.uCallbackMessage = WM_ICON_NOTIFY;//应用程序定义的回调消息ID

	CString szToolTip;
	szToolTip = _T("INeed 客户端程序");
	_tcscpy_s(m_tnid.szTip, szToolTip);//帮助信息 
	m_tnid.uID = IDR_MAINFRAME;//应用程序图标  
	m_tnid.hIcon = m_hIcon;//图标句柄 
	PNOTIFYICONDATA m_ptnid = &m_tnid;
	::Shell_NotifyIcon(NIM_ADD, m_ptnid);//增加图标到系统盘


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFC07trayiconDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
	if (nID == SC_MINIMIZE)
	{
		ShowWindow(FALSE); //隐藏窗口
	}


}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFC07trayiconDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFC07trayiconDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC07trayiconDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	NOTIFYICONDATA   nd = { 0 };
	nd.cbSize = sizeof(NOTIFYICONDATA);
	nd.hWnd = m_hWnd;
	nd.uID = IDR_MAINFRAME;
	nd.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nd.uCallbackMessage = WM_ICON_NOTIFY;
	nd.hIcon = m_hIcon;
	Shell_NotifyIcon(NIM_DELETE, &nd);

	CDialogEx::OnClose();
}

LRESULT CMFC07trayiconDlg::OnTrayNotification(WPARAM wParam, LPARAM lParam)
{
	switch (lParam)
	{
	case WM_LBUTTONDOWN:
	{
		AfxGetApp()->m_pMainWnd->ShowWindow(SW_SHOWNORMAL);
		SetForegroundWindow();
		break;
	}
	case WM_RBUTTONUP:
	{
		POINT point;
		HMENU hMenu, hSubMenu;
		GetCursorPos(&point); //鼠标位置
		hMenu = LoadMenu(NULL,
			MAKEINTRESOURCE(IDR_MENU_TRAY)); // 加载菜单
		hSubMenu = GetSubMenu(hMenu, 0);//得到子菜单(因为弹出式菜单是子菜单)
		SetForegroundWindow(); // 激活窗口并置前

		TrackPopupMenu(hSubMenu, 0,
			point.x, point.y, 0, m_hWnd, NULL);

	}
	}
	return LRESULT();
}


void CMFC07trayiconDlg::OnTrayRestore()
{
	// TODO: 在此添加命令处理程序代码
	AfxGetApp()->m_pMainWnd->ShowWindow(SW_SHOWNORMAL);
	SetForegroundWindow();
}


void CMFC07trayiconDlg::OnTrayExit()
{
	// TODO: 在此添加命令处理程序代码
	OnClose();
}
