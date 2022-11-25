
// ClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "afxdialogex.h"
#include "Client.h"
#include "ClientDlg.h"
#include "SocketClient.h"
#include "SetUpDlg.h"
#include "LoginDlg.h"
#include "ChargeDlg.h"
#include "RegisterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
public:
	;
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}



// CClientDlg 对话框



CClientDlg::CClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_DISPLAY, m_editDisplay);
	DDX_Control(pDX, IDC_EDIT_VALUE, m_editValue);
	DDX_Control(pDX, IDC_EDIT_ACCOUNT, m_editAccount);
}


BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_STN_CLICKED(IDC_DISPLAY, &CClientDlg::OnStnClickedDisplay)
	ON_BN_CLICKED(IDC_BUTTON_AC, &CClientDlg::OnBnClickedButtonAC)
	ON_BN_CLICKED(IDC_BUTTON0, &CClientDlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON1, &CClientDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CClientDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CClientDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CClientDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CClientDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CClientDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CClientDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CClientDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CClientDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CClientDlg::OnBnClickedButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_LP, &CClientDlg::OnBnClickedButtonLp)
	ON_BN_CLICKED(IDC_BUTTON_RP, &CClientDlg::OnBnClickedButtonRp)
	ON_BN_CLICKED(IDC_BUTTON_DOT, &CClientDlg::OnBnClickedButtonDot)
	ON_BN_CLICKED(IDC_BUTTON_PLUS, &CClientDlg::OnBnClickedButtonPlus)
	ON_BN_CLICKED(IDC_BUTTON_MINUS, &CClientDlg::OnBnClickedButtonMinus)
	ON_BN_CLICKED(IDC_BUTTON_MCL, &CClientDlg::OnBnClickedButtonMcl)
	ON_BN_CLICKED(IDC_BUTTON_DIV, &CClientDlg::OnBnClickedButtonDiv)
	ON_COMMAND(ID_ABOUT, &CClientDlg::OnAbout)
	ON_COMMAND(ID_SETUP, &CClientDlg::OnSetUp)
	ON_MESSAGE(WM_LOGIN, &CClientDlg::OnLogin)
	ON_MESSAGE(WM_REGISTER, &CClientDlg::OnRegister)
	ON_BN_CLICKED(IDC_BUTTON_CHARGE, &CClientDlg::OnBnClickedButtonCharge)
	ON_COMMAND(ID_CHARGE, &CClientDlg::OnCharge)
	ON_BN_CLICKED(IDC_BUTTON_EQUAL, &CClientDlg::OnBnClickedButtonEqual)
END_MESSAGE_MAP()


// CClientDlg 消息处理程序

BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。
	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SetUpDlg = new CSetUpDlg;
	InitSocketClient();

	// 设置文本框显示的字体
	CFont displayFont;
	displayFont.CreatePointFont(150, _T("黑体"), NULL);
	m_editDisplay.SetFont(&displayFont);

	ShowLoginDlg();

	// 初始化文本框中显示的文字
	m_strDisplay = "";
	m_editDisplay.SetWindowTextW(TEXT("0"));

	// 用户信息初始化
	m_editAccount.SetWindowTextW(m_account);
	m_editValue.SetWindowTextW(m_value);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CClientDlg::OnStnClickedDisplay()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CClientDlg::OnBnClickedButton0()
{
	m_strDisplay += "0";
	SetDlgItemText(IDC_DISPLAY, m_strDisplay);
}


void CClientDlg::OnBnClickedButton1()
{
	m_strDisplay += "1";
	SetDlgItemText(IDC_DISPLAY, m_strDisplay);

}

void CClientDlg::OnBnClickedButton2()
{
	m_strDisplay += "2";
	SetDlgItemText(IDC_DISPLAY, m_strDisplay);
}

void CClientDlg::OnBnClickedButton3()
{
	m_strDisplay += "3";
	SetDlgItemText(IDC_DISPLAY, m_strDisplay);
}


void CClientDlg::OnBnClickedButton4()
{
	m_strDisplay += "4";
	SetDlgItemText(IDC_DISPLAY, m_strDisplay);
}


void CClientDlg::OnBnClickedButton5()
{
	m_strDisplay += "5";
	SetDlgItemText(IDC_DISPLAY, m_strDisplay);
}


void CClientDlg::OnBnClickedButton6()
{
	m_strDisplay += "6";
	SetDlgItemText(IDC_DISPLAY, m_strDisplay);
}


void CClientDlg::OnBnClickedButton7()
{
	m_strDisplay += "7";
	SetDlgItemText(IDC_DISPLAY, m_strDisplay);
}


void CClientDlg::OnBnClickedButton8()
{
	m_strDisplay += "8";
	SetDlgItemText(IDC_DISPLAY, m_strDisplay);
}


void CClientDlg::OnBnClickedButton9()
{
	m_strDisplay += "9";
	SetDlgItemText(IDC_DISPLAY, m_strDisplay);
}


void CClientDlg::OnBnClickedButtonDel()
{
	if (m_strDisplay.IsEmpty())
	{
		SetDlgItemText(IDC_DISPLAY, L"0");
	}
	else if (m_strDisplay.GetLength() == 1)
	{
		m_strDisplay = m_strDisplay.Left(m_strDisplay.GetLength() - 1);
		SetDlgItemText(IDC_DISPLAY, L"0");
	}
	else
	{
		m_strDisplay = m_strDisplay.Left(m_strDisplay.GetLength() - 1);
		SetDlgItemText(IDC_DISPLAY, m_strDisplay);
	}
}


void CClientDlg::OnBnClickedButtonAC()
{
	m_strDisplay.Empty();
	SetDlgItemText(IDC_DISPLAY, TEXT("0"));
}


// 菜单中打开关于界面
void CClientDlg::OnAbout()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg AboutDlg;
	AboutDlg.DoModal();
}

BOOL CClientDlg::MsgGenerator(char szBuf[], CString userName, CString userPassword, CString textSend, UINT nRequest, UINT nStatus)
{
	USES_CONVERSION;
	CString strMsg;
	UINT userNameLen = userName.GetLength();
	CString strUserNameLen;
	if (userNameLen > 0 && userNameLen < 9) {
		strUserNameLen.Format(L"0%d", userNameLen);
	}
	else
	{
		strUserNameLen.Format(L"%d", userNameLen);
	}
	UINT PasswordLen = userPassword.GetLength();
	CString strPasswordLen;
	if (PasswordLen > 0 && PasswordLen < 9) {
		strPasswordLen.Format(L"0%d", PasswordLen);
	}
	else
	{
		strPasswordLen.Format(L"%d", PasswordLen);
	}
	strMsg.Format(L"%d%d%s%s%s%s%s", nRequest, nStatus, strUserNameLen, strPasswordLen, userName, userPassword, textSend);
	strcpy_s(szBuf, MAX_BUF, T2A(strMsg));
	return TRUE;
}


LRESULT CClientDlg::OnLogin(WPARAM, LPARAM)
{
	MsgSend(m_account, m_password, L"0", REQUEST_LOGIN);
	return LRESULT();
}

LRESULT CClientDlg::OnRegister(WPARAM, LPARAM)
{
	MsgSend(m_account, m_password, L"0", REQUEST_REGISTER);
	return LRESULT();
}

void CClientDlg::InitSocketClient()
{
	m_ptrSocketClient = new CSocketClient(this);
	m_IPAddress = SetUpDlg->m_IPAddress;
	m_Port = SetUpDlg->m_Port;
	CString strMsg;
	if (m_ptrSocketClient == NULL)
	{
		strMsg.Format(L"初始化失败.错误码:%d", GetLastError());
		MessageBox(strMsg, L"提示", MB_OK | MB_ICONERROR);
	}
	//创建套接字
	if (m_ptrSocketClient->Create() == FALSE)
	{
		strMsg.Format(L"初始化失败.错误码:%d", GetLastError());
		MessageBox(strMsg, L"提示", MB_OK | MB_ICONERROR);
	}
	//连接服务器
	if (m_ptrSocketClient->Connect(m_IPAddress, m_Port) == FALSE)
	{
		strMsg.Format(L"连接服务器失败.错误码:%d", GetLastError());
		MessageBox(strMsg, L"提示", MB_OK | MB_ICONERROR);
		exit(0);	//无法连接服务器，强制退出
	}
}

void CClientDlg::ShowLoginDlg()
{
	LoginDlg = new CLoginDlg(this);
	LoginDlg->DoModal();
}


void CClientDlg::OnLoginSuccess()
{
	LoginDlg->OnOK();
}

void CClientDlg::OnLoginFail()
{
	AfxMessageBox(L"登陆失败！");
}

void CClientDlg::OnRegisterSuccess()
{
	LoginDlg->CloseRegistorDlg();
}

void CClientDlg::OnRegisterFail()
{
	AfxMessageBox(L"登陆失败！");
}

void CClientDlg::OnSetUp()
{
	// TODO: 在此添加命令处理程序代码
	SetUpDlg->DoModal();


	//this->ShowWindow(SW_HIDE);
	//OnInitDialog();
	//this->ShowWindow(SW_SHOW);
}


void CClientDlg::OnBnClickedButtonLp()
{
	m_strDisplay += "(";
	SetDlgItemText(IDC_DISPLAY, m_strDisplay);
}


void CClientDlg::OnBnClickedButtonRp()
{
	m_strDisplay += ")";
	SetDlgItemText(IDC_DISPLAY, m_strDisplay);
}


void CClientDlg::OnBnClickedButtonDot()
{
	if (m_strDisplay.IsEmpty() == TRUE)
	{
		m_strDisplay += "0";
	}
	m_strDisplay += ".";
	SetDlgItemText(IDC_DISPLAY, m_strDisplay);
}

void CClientDlg::OnBnClickedButtonPlus()
{
	m_strDisplay += "+";
	SetDlgItemText(IDC_DISPLAY, m_strDisplay);
}

void CClientDlg::OnBnClickedButtonMinus()
{
	m_strDisplay += "-";
	SetDlgItemText(IDC_DISPLAY, m_strDisplay);
}

void CClientDlg::OnBnClickedButtonMcl()
{
	m_strDisplay += "*";
	SetDlgItemText(IDC_DISPLAY, m_strDisplay);
}

void CClientDlg::OnBnClickedButtonDiv()
{
	m_strDisplay += "/";
	SetDlgItemText(IDC_DISPLAY, m_strDisplay);
}

void CClientDlg::OnBnClickedButtonCharge()
{
	OnCharge();
}


void CClientDlg::OnCharge()
{
	ChargeDlg = new CChargeDlg(this);
	ChargeDlg->DoModal();
}

void CClientDlg::OnChargeSuccess(DOUBLE chargeVal)
{
	m_value.Format(L"%.2f", (_ttof(m_value) + chargeVal));
	AfxMessageBox(L"充值成功！");
	ChargeDlg->RefreshUserVal();
	m_editValue.SetWindowTextW(m_value);
}


void CClientDlg::MsgSend(CString username, CString userPassword, CString textSend, UINT nRequest, UINT nStatus)
{
	char szBuf[MAX_BUF] = { "0" };
	MsgGenerator(szBuf, username, userPassword, textSend, nRequest, nStatus);
	m_ptrSocketClient->Send(szBuf, MAX_BUF);
}

void CClientDlg::ChargeVal(DOUBLE chargeVal)
{
	CString strChargeVal;
	strChargeVal.Format(L"%.2f", chargeVal);
	MsgSend(m_account, m_password, strChargeVal, REQUEST_CHARGE);
}


void CClientDlg::OnBnClickedButtonEqual()
{
	// TODO: 在此添加控件通知处理程序代码
	MsgSend(m_account, m_password, m_strDisplay, REQUEST_CALCULATE);
}

void CClientDlg::OnCalculateSuccess(CString result)
{
	m_strDisplay = result;
	m_editDisplay.SetWindowTextW(m_strDisplay);
	CString strMsg;
	strMsg.Format(L"计算成功，结果:%s", result);
	MessageBox(strMsg, L"提示", MB_ICONINFORMATION);
}
