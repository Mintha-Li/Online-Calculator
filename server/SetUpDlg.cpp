// SetUpDlg.cpp: 实现文件
//

#include "pch.h"
#include "Server.h"
#include "SetUpDlg.h"
#include "afxdialogex.h"
#include "ServerDlg.h"


// CSetUpDlg 对话框

IMPLEMENT_DYNAMIC(CSetUpDlg, CDialogEx)

CSetUpDlg::CSetUpDlg(CServerDlg* pDlg, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETUP, pParent)
	, m_Port(0)
{
	m_pMainDlg = pDlg;
}

CSetUpDlg::~CSetUpDlg()
{
}

void CSetUpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS, m_IPAddressCtrl);
	DDX_Text(pDX, IDC_EDIT_PORT, m_Port);
	DDX_Control(pDX, IDC_EDIT_COST, m_editCost);
}


BEGIN_MESSAGE_MAP(CSetUpDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &CSetUpDlg::OnBnClickedButtonApply)
END_MESSAGE_MAP()


// CSetUpDlg 消息处理程序
BOOL CSetUpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_IPAddress = "127.0.0.1";
	m_Port = 8080;
	// TODO:  在此添加额外的初始化
	m_IPAddressCtrl.SetWindowTextW(m_IPAddress);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CSetUpDlg::OnBnClickedButtonApply()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_IPAddressCtrl.GetWindowText(m_IPAddress);
	m_pMainDlg->m_IPAddress = m_IPAddress;
	m_pMainDlg->m_Port = m_Port;
}