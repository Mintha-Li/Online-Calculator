#pragma once


// CLogin 对话框
class CRegisterDlg;
class CClientDlg;
class CRegisterDlg;
class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CClientDlg *pDlg,CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CLoginDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	CClientDlg *pMainDlg;
public:
	virtual BOOL OnInitDialog();
	CFont staticTitleFont;
	CStatic m_staticTitle;
	CEdit m_editAccount;
	CEdit m_editPassword;
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedButtonRegistor();
	virtual void OnOK();
	CRegisterDlg *RegistorDlg;
	void CloseRegistorDlg();
};
