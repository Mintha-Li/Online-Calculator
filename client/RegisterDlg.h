#pragma once


// CRegistorDlg 对话框

class CRegisterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRegisterDlg)

public:
	CRegisterDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CRegisterDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REGISTOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CFont staticTitleFont;
	CStatic m_staticTitle;
	afx_msg void OnBnClickedButtonRst();
	CEdit m_editAccount;
	CEdit m_editPassword;
	CEdit m_editPwCheck;
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
