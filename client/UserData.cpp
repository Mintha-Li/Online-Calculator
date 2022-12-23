// UserData.cpp: 实现文件
//

#include "pch.h"
#include "Client.h"
#include "UserData.h"
#include "afxdialogex.h"
#include "ClientDlg.h"

// CUserData 对话框

IMPLEMENT_DYNAMIC(CUserData, CDialogEx)

CUserData::CUserData(CClientDlg* pDlg,CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_USERDATA, pParent)
{
	pMainDlg = pDlg;
}

CUserData::~CUserData()
{
}

void CUserData::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ACCOUNT, m_editAccount);
	DDX_Control(pDX, IDC_EDIT_VALUE, m_editValue);
	DDX_Control(pDX, IDC_EDIT_PW, m_editPassword);
	DDX_Control(pDX, IDC_EDIT_PWCHECK, m_editPWCheck);
}


BEGIN_MESSAGE_MAP(CUserData, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &CUserData::OnBnClickedButtonApply)
END_MESSAGE_MAP()


// CUserData 消息处理程序


void CUserData::OnBnClickedButtonApply()
{
	// TODO: 在此添加控件通知处理程序代码
	CString m_pw;
	CString m_pwcheck;
	m_editPassword.GetWindowTextW(m_pw);
	m_editPWCheck.GetWindowTextW(m_pwcheck);
	if (m_pw == m_pwcheck) {
		MessageBox(L"请重新登录！", L"提示", MB_OK | MB_ICONINFORMATION);
		OnOK();
		pMainDlg->OnUserDataChange(m_pw);
	}
	else
	{
		MessageBox(L"两次输入的密码不一致！", L"提示", MB_OK | MB_ICONERROR);
	}
}


BOOL CUserData::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitUserData();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CUserData::InitUserData()
{
	m_editAccount.SetWindowTextW(pMainDlg->m_account);
	m_editValue.SetWindowTextW(pMainDlg->m_value);
}


void CUserData::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnOK();
}
