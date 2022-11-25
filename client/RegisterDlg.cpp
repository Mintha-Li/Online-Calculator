// RegistorDlg.cpp: 实现文件
//

#include "pch.h"
#include "Client.h"
#include "RegisterDlg.h"
#include "afxdialogex.h"
#include "ClientDlg.h"


// CRegistorDlg 对话框

IMPLEMENT_DYNAMIC(CRegisterDlg, CDialogEx)

CRegisterDlg::CRegisterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REGISTER, pParent)
{

}

CRegisterDlg::~CRegisterDlg()
{
}

void CRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TITLE2, m_staticTitle);
	DDX_Control(pDX, IDC_EDIT_ACCT, m_editAccount);
	DDX_Control(pDX, IDC_EDIT_PW, m_editPassword);
	DDX_Control(pDX, IDC_EDIT_PWCHECK, m_editPwCheck);
}


BEGIN_MESSAGE_MAP(CRegisterDlg, CDialogEx)

	ON_BN_CLICKED(IDC_BUTTON_RST, &CRegisterDlg::OnBnClickedButtonRst)
END_MESSAGE_MAP()


// CRegistorDlg 消息处理程序


BOOL CRegisterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	staticTitleFont.CreatePointFont(150, _T("楷体"));
	m_staticTitle.SetFont(&staticTitleFont);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CRegisterDlg::OnBnClickedButtonRst()
{
	UpdateData();
	CString m_acct;
	CString m_pw;
	CString m_pwcheck;
	m_editAccount.GetWindowTextW(m_acct);
	m_editPassword.GetWindowTextW(m_pw);
	m_editPwCheck.GetWindowTextW(m_pwcheck);
	CClientDlg *pParent = (CClientDlg*)(AfxGetMainWnd());
	if (m_pw == m_pwcheck) {
		pParent->m_account = m_acct;
		pParent->m_password = m_pw;
		::SendMessage(::AfxGetMainWnd()->m_hWnd, WM_REGISTER, 0, 0);
	}
	else
	{
		MessageBox(L"两次输入的密码不一致！", L"提示", MB_OK | MB_ICONERROR);
	}
}


void CRegisterDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	MessageBox(L"注册成功！", L"提示", MB_ICONINFORMATION);
	CDialogEx::OnOK();
}
