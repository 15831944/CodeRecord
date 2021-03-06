
// MFC_03_CListCtrlDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFC_03_CListCtrl.h"
#include "MFC_03_CListCtrlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CMFC03CListCtrlDlg 对话框

DWORD CMFC03CListCtrlDlg::m_SortColum = 0;
BOOL CMFC03CListCtrlDlg::m_bAs = TRUE;



int   CALLBACK CMFC03CListCtrlDlg::MyListCompar(LPARAM   lParam1, LPARAM   lParam2, LPARAM   lParamSort)
{
	//通过传递的参数来得到CSortList对象指针，从而得到排序方式 
	CListCtrl* pListCtrl = (CListCtrl*)lParamSort;

	//通过ItemData来确定数据 

	int   iCompRes;
	CString    szComp1 = pListCtrl->GetItemText(lParam1, m_SortColum);
	CString    szComp2 = pListCtrl->GetItemText(lParam2, m_SortColum);

	switch (m_SortColum)
	{
		// 这里是要修改的部分，要根据有整数的列进行排序。2是代表第三列为整数
	case(2): {
		//以第一列为根据排序   编号
		//_ttol 
		iCompRes = _ttol(szComp1) <= _ttol(szComp2) ? -1 : 1;
		break;
	}
	default:
		iCompRes = szComp1.Compare(szComp2);
		break;
	}
	//根据当前的排序方式进行调整

	if (m_bAs)
		return   iCompRes;
	else
		return   -iCompRes;
}

CMFC03CListCtrlDlg::CMFC03CListCtrlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_03_CLISTCTRL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC03CListCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listCtrl);
}

BEGIN_MESSAGE_MAP(CMFC03CListCtrlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CMFC03CListCtrlDlg::OnNMRClickList1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CMFC03CListCtrlDlg::OnNMClickList1)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, &CMFC03CListCtrlDlg::OnLvnColumnclickList1)
END_MESSAGE_MAP()


// CMFC03CListCtrlDlg 消息处理程序

BOOL CMFC03CListCtrlDlg::OnInitDialog()
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








	// 表头添加
	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_listCtrl.InsertColumn(0, _T("网站来源"), LVCFMT_LEFT, 85);
	m_listCtrl.InsertColumn(1, _T("产品"), LVCFMT_LEFT, 110);
	m_listCtrl.InsertColumn(2, _T("价格"), LVCFMT_LEFT, 80);

	// 插入值
	int iLine = m_listCtrl.GetItemCount();             // 列表的里面的条目数量, 横着的行
	m_listCtrl.InsertItem(iLine, _T("SOHU"));          // 第一行第一列
	m_listCtrl.SetItemText(iLine, 1, _T("IPHONE"));   // 第一行第二列
	m_listCtrl.SetItemText(iLine, 2, _T("5000"));     // 第一行第三列

	// 最末行添加数据
	iLine = m_listCtrl.GetItemCount();
	m_listCtrl.InsertItem(iLine, _T("TAOBAO"));        // 第二行第一列
	m_listCtrl.SetItemText(iLine, 1, _T("奔驰"));     // 第二行第二列    
	m_listCtrl.SetItemText(iLine, 2, _T("500000"));   // 第二行第三列 

	iLine = m_listCtrl.GetItemCount();
	m_listCtrl.InsertItem(iLine, _T("GOOGLE"));        // 第三行第一列
	m_listCtrl.SetItemText(iLine, 1, _T("宝马"));     // 第三行第二列
	m_listCtrl.SetItemText(iLine, 2, _T("600000"));   // 第三行第三列








	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFC03CListCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFC03CListCtrlDlg::OnPaint()
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
HCURSOR CMFC03CListCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC03CListCtrlDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_istat = m_listCtrl.GetSelectionMark();       //用istat存放当前选定的是第几项
	m_szSite = m_listCtrl.GetItemText(m_istat, 0);//获取当前项中的数据，0代表是第0列
	m_szProduct = m_listCtrl.GetItemText(m_istat, 1);
	m_szValue = m_listCtrl.GetItemText(m_istat, 2);
	m_iValue = _ttol(m_listCtrl.GetItemText(m_istat, 2));

	POINT point;
	HMENU hMenu, hSubMenu;
	GetCursorPos(&point);                   //鼠标位置
	hMenu = LoadMenu(NULL,
		MAKEINTRESOURCE(IDR_MENU_TOPICR));  // 加载菜单
	hSubMenu = GetSubMenu(hMenu, 0);        //得到子菜单(因为弹出式菜单是子菜单)

	SetMenuDefaultItem(hSubMenu, -1, FALSE);//设置缺省菜单项,-1为无缺省项
	SetForegroundWindow();                  // 激活窗口并置前

	TrackPopupMenu(hSubMenu, 0,
		point.x, point.y, 0, m_hWnd, NULL);
	*pResult = 0;
}


void CMFC03CListCtrlDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	int istat = m_listCtrl.GetSelectionMark();          //用istat存放当前选定的是第几项
	CString szSite = m_listCtrl.GetItemText(istat, 0); //获取当前项中的数据，0代表是第0列
	CString szProduct = m_listCtrl.GetItemText(istat, 1);   // 第一列
	CString szValue = m_listCtrl.GetItemText(istat, 2);     // 第二列
	UINT iValue = _ttol(m_listCtrl.GetItemText(istat, 2));

	MessageBox(szSite, szProduct + szValue, MB_OK);

	*pResult = 0;
}


void CMFC03CListCtrlDlg::OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	m_SortColum = pNMListView->iSubItem;
	m_bAs = !m_bAs;//升序还是降序


	int count = m_listCtrl.GetItemCount();   //行数
	for (int i = 0; i < count; i++)
	{
		m_listCtrl.SetItemData(i, i);
	}
	m_listCtrl.SortItems(MyListCompar, (LPARAM)&m_listCtrl);
	*pResult = 0;
}
