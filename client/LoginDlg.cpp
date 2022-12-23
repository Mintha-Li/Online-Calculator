// LoginDlg.cpp: 实现文件
//

#include "pch.h"
#include "Client.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "ClientDlg.h"
#include "RegisterDlg.h"

// CLogin 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CClientDlg *pDlg,CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN, pParent)
{
	pMainDlg = pDlg;		//将主窗口句柄传入
}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TITLE, m_staticTitle);
	DDX_Control(pDX, IDC_EDIT_ACCOUNT, m_editAccount);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_editPassword);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CLoginDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_REGISTOR, &CLoginDlg::OnBnClickedButtonRegistor)
END_MESSAGE_MAP()


// CLogin 消息处理程序


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	this->ModifyStyleEx(0, WS_EX_APPWINDOW);

	staticTitleFont.CreatePointFont(150, _T("楷体"));
	m_staticTitle.SetFont(&staticTitleFont);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CLoginDlg::OnClose()
{
	// 若关闭登录窗口，程序应退出
	if (MessageBox(L"确认退出？", L"提示", MB_YESNO | MB_ICONINFORMATION) == IDYES)
	{
		CDialogEx::OnClose();
		exit(0);
	}
	return;
}


void CLoginDlg::OnBnClickedButtonLogin()
{
	UpdateData();
	CString m_acct;
	CString m_pw;
	m_editAccount.GetWindowTextW(m_acct);			//获取用户名
	m_editPassword.GetWindowTextW(m_pw);			//获取密码
	CClientDlg *pParent = (CClientDlg*)GetParent();	//获取主窗口句柄
	pParent->m_account=m_acct;						//将用户名和密码传入主窗口
	pParent->m_password = m_pw;						
	//发送自定义消息，主窗口执行实现登录
	::SendMessage(::AfxGetMainWnd()->m_hWnd, WM_LOGIN, 0, 0);
}


void CLoginDlg::OnBnClickedButtonRegistor()
{
	RegistorDlg = new CRegisterDlg;
	RegistorDlg->DoModal();
}


void CLoginDlg::OnOK()
{
	MessageBox(L"登陆成功！",L"提示",MB_ICONINFORMATION);
	CDialogEx::OnOK();
}

void CLoginDlg::CloseRegistorDlg()
{
	RegistorDlg->OnOK();
}


BOOL CLoginDlg::PreTranslateMessage(MSG* pMsg)
{
	// 修改Enter定义
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		OnBnClickedButtonLogin();
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
