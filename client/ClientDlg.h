
// ClientDlg.h: 头文件
//

#pragma once
class CSocketClient;
class CSetUpDlg;
class CLoginDlg;
class CChargeDlg;
// CClientDlg 对话框
class CClientDlg : public CDialogEx
{
	// 构造
public:
	CClientDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLIENT_DIALOG };
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
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 数据的显示
	afx_msg void OnStnClickedDisplay();

	// 按键
	afx_msg void OnBnClickedButtonAC();
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedButtonLp();
	afx_msg void OnBnClickedButtonRp();
	afx_msg void OnBnClickedButtonDot();
	afx_msg void OnBnClickedButtonPlus();
	afx_msg void OnBnClickedButtonMinus();
	afx_msg void OnBnClickedButtonMcl();
	afx_msg void OnBnClickedButtonDiv();
	afx_msg void OnBnClickedButtonEqual();

	// 其他功能按键
	afx_msg void OnBnClickedButtonCharge();

	// 自定义消息响应
	afx_msg LRESULT OnLogin(WPARAM, LPARAM);
	afx_msg LRESULT OnRegister(WPARAM, LPARAM);

	// 初始化函数
	afx_msg void InitSocketClient();
	afx_msg void ShowLoginDlg();

	// 算式显示部分
	// 显示编辑框
	CEdit m_editDisplay;
	// 显示文本
	CString m_strDisplay;

	// 用户信息
	CString m_account;
	CString m_password;
	CString m_value;
	DOUBLE m_chargeValue;

	// Socket
	CSocketClient *m_ptrSocketClient;
	CString m_IPAddress;
	UINT m_Port;

	CSetUpDlg *SetUpDlg;
	CLoginDlg *LoginDlg;
	CChargeDlg *ChargeDlg;


	afx_msg void OnSetUp();

	// 菜单按键
	afx_msg void OnAbout();

	// 格式化发送数据生成函数
	BOOL MsgGenerator(char szBuf[], CString userName, CString userPassword, CString textSend,
		UINT nRequest = REQUEST_NONE, UINT nStatus = STATUS_NONE);
	afx_msg void OnCharge();



	CEdit m_editValue;
	CEdit m_editAccount;
	void MsgSend(CString username, CString userPassword, CString textSend = L"0", UINT nRequest = REQUEST_NONE, UINT nStatus = STATUS_NONE);
	void ChargeVal(DOUBLE chargeVal);

	void OnLoginSuccess();
	void OnLoginFail();
	void OnRegisterSuccess();
	void OnRegisterFail();
	void OnChargeSuccess(DOUBLE chargeVal);
	//void OnChargeFail();
	void OnCalculateSuccess(CString result);
	//void OnCalculateFail();
};
