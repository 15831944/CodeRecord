#pragma once


// CShowMsgDlg 对话框

class CShowMsgDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CShowMsgDlg)

public:
	CShowMsgDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CShowMsgDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ShowMsgDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	CString m_szID;
//	CEdit m_szPASS;
	afx_msg void OnBnClickedBtnFunction();
	CString m_szPWD;
	CString m_szUSER;
};
