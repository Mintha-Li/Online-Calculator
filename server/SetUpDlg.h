#pragma once


// CSetUpDlg 对话框
class CServerDlg;
class CSetUpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetUpDlg)

public:
	CSetUpDlg(CServerDlg* pDlg,CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSetUpDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETUP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_IPAddress;
	UINT m_Port;
	CIPAddressCtrl m_IPAddressCtrl;
	CServerDlg *m_pMainDlg;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonApply();
	CEdit m_editCost;
};
