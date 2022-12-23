#pragma once


// CUserData 对话框
class CClientDlg;
class CUserData : public CDialogEx
{
	DECLARE_DYNAMIC(CUserData)

public:
	CUserData(CClientDlg* pDlg,CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CUserData();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USERDATA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CClientDlg *pMainDlg;
public:
	CEdit m_editAccount;
	CEdit m_editValue;
	CEdit m_editPassword;
	CEdit m_editPWCheck;
	afx_msg void OnBnClickedButtonApply();
	virtual BOOL OnInitDialog();
public:
	void InitUserData();
	virtual void OnOK();
};
