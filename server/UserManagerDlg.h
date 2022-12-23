#pragma once

class CServerDlg;
class CInfoFile;
// CUserManagerDlg 对话框
class CUserManagerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUserManagerDlg)

public:
	CUserManagerDlg(CServerDlg* pDlg, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CUserManagerDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USER_MANAGER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_UserDataList;
private:
	CServerDlg* m_pMainDlg;
	CInfoFile *m_pUserData;
public:
	void UpdateListData(BOOL status = TRUE);
	afx_msg void OnBnClickedButtonDelUser();
	afx_msg void OnBnClickedButtonAdduser();
	CEdit m_editAccount;
	CEdit m_editPassword;
	CEdit m_editValue;
	afx_msg void OnBnClickedButtonSave();
	CEdit m_editUsername;
	afx_msg void OnBnClickedButtonFind();
};
