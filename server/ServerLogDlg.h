#pragma once


// CServerLogDlg 对话框

class CServerDlg;
class CServerLogDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CServerLogDlg)

public:
	CServerLogDlg(CServerDlg* pDlg,CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CServerLogDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVERLOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	CServerDlg* m_pMainDlg;
public:
	CEdit m_editLog;
	CString m_ServerLog;
	CString GetTime();
public:
	afx_msg void OnBnClickedButtonServerOn();
	afx_msg void AddServerLog(LPCTSTR strMsg);
	afx_msg void OnBnClickedButtonServerOff();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSavelog();
};
