
// MFC_05_TabCtrlDlg.h: 头文件
//

#pragma once
#include "CPAGEFile.h"
#include "CPAGENet.h"
#include "CPAGEProc.h"

// CMFC05TabCtrlDlg 对话框
class CMFC05TabCtrlDlg : public CDialogEx
{
// 构造
public:
	CMFC05TabCtrlDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_05_TABCTRL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	
	//Tab
	CPAGEFile m_FilePage;
	CPAGENet  m_NetPage;
	CPAGEProc m_ProcPage;

#define MAX_DLG_PAGE 5
	CDialog		 *m_pDialog[MAX_DLG_PAGE];
	int			 m_CurSelTab;


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tabCtrl;
	afx_msg void OnTcnSelchangeTabDemo(NMHDR *pNMHDR, LRESULT *pResult);
};
