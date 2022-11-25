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
	pMainDlg = pDlg;
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

	// TODO:  在此添加额外的初始化
	staticTitleFont.CreatePointFont(150, _T("楷体"));
	m_staticTitle.SetFont(&staticTitleFont);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CLoginDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CString m_acct;
	CString m_pw;
	m_editAccount.GetWindowTextW(m_acct);
	m_editPassword.GetWindowTextW(m_pw);
	CClientDlg *pParent = (CClientDlg*)GetParent();
	pParent->m_account=m_acct;
	pParent->m_password = m_pw;
	::SendMessage(::AfxGetMainWnd()->m_hWnd, WM_LOGIN, 0, 0);
}


void CLoginDlg::OnBnClickedButtonRegistor()
{
	// TODO: 在此添加控件通知处理程序代码
	RegistorDlg = new CRegisterDlg;
	RegistorDlg->DoModal();
}


void CLoginDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	AfxMessageBox(L"登陆成功！");
	CDialogEx::OnOK();
}

void CLoginDlg::CloseRegistorDlg()
{
	RegistorDlg->OnOK();
}
