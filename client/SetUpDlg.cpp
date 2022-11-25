// CSetUpDlg.cpp: 实现文件
//

#include "pch.h"
#include "Client.h"
#include "SetUpDlg.h"
#include "afxdialogex.h"


// CSetUpDlg 对话框

IMPLEMENT_DYNAMIC(CSetUpDlg, CDialogEx)

CSetUpDlg::CSetUpDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETUP, pParent)
	, m_Port(8080)
{
	m_IPAddress = "127.0.0.1";
	m_Port = 8080;
}

CSetUpDlg::~CSetUpDlg()
{
}

void CSetUpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS, m_IPAddressCtrl);
	DDX_Text(pDX, IDC_EDIT_PORT, m_Port);
}


BEGIN_MESSAGE_MAP(CSetUpDlg, CDialogEx)

	ON_BN_CLICKED(IDOK, &CSetUpDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSetUpDlg 消息处理程序



void CSetUpDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_IPAddressCtrl.GetWindowText(m_IPAddress);
	UpdateData();
	CDialogEx::OnOK();
}


BOOL CSetUpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_IPAddressCtrl.SetWindowTextW(m_IPAddress);
	m_Port = 8080;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
