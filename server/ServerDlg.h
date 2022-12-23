
// serverDlg.h: 头文件
//

#pragma once


class CSocketListen;
class CServerLogDlg;
class CUserManagerDlg;
class CSetUpDlg;
class CInfoFile;

// CserverDlg 对话框
class CServerDlg : public CDialogEx
{
// 构造
public:
	CServerDlg(CWnd* pParent = nullptr);	// 标准构造函数
	~CServerDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void InitSocketListen();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	//通信部分
	CSocketListen *m_ptrListen;
	CString m_IPAddress;
	UINT m_Port;
	void OnAccept();
	BOOL ServerOn();
	BOOL ServerOff();
	void SaveLog();
	BOOL ServerStatus = FALSE;
public:
	//界面部分
	CTabCtrl m_TabMain;
	int m_CurSelTab;
	CSetUpDlg *m_SetUpDlg;
	CUserManagerDlg *m_UserManagerDlg;
	CServerLogDlg *m_ServerLogDlg;
	CDialogEx *pDialog[3];						// 用于保存对话框对象指针
	void InitTabMain();
	afx_msg void OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClose();
public:
	//用户信息部分
	CInfoFile *m_UserData;
	void InitUserData();
public:
	DOUBLE m_valCost;
};
