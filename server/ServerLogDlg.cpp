// ServerLogDlg.cpp: 实现文件
//

#include "pch.h"
#include "Server.h"
#include "ServerLogDlg.h"
#include "ServerDlg.h"
#include "afxdialogex.h"


// CServerLogDlg 对话框

IMPLEMENT_DYNAMIC(CServerLogDlg, CDialogEx)

CServerLogDlg::CServerLogDlg(CServerDlg * pDlg,CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SERVERLOG, pParent)
{
	m_pMainDlg = pDlg;
}


CServerLogDlg::~CServerLogDlg()
{
}

void CServerLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_LOG, m_editLog);
}

// 获取系统时间，并按%Y-%m-%d %H:%M:%S格式返回
CString CServerLogDlg::GetTime()
{
	CTime time = CTime::GetCurrentTime();
	CString strTime = time.Format(_T("%Y-%m-%d %H:%M:%S"));
	return strTime;
}


BEGIN_MESSAGE_MAP(CServerLogDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SERVERON, &CServerLogDlg::OnBnClickedButtonServerOn)
	ON_BN_CLICKED(IDC_BUTTON_SERVEROFF, &CServerLogDlg::OnBnClickedButtonServerOff)
	ON_BN_CLICKED(IDC_BUTTON_SAVELOG, &CServerLogDlg::OnBnClickedButtonSavelog)
END_MESSAGE_MAP()


// CServerLogDlg 消息处理程序


void CServerLogDlg::OnBnClickedButtonServerOn()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pMainDlg->ServerOn();
	GetDlgItem(IDC_BUTTON_SERVERON)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SERVEROFF)->EnableWindow(TRUE);
}

void CServerLogDlg::AddServerLog(LPCTSTR m_strLog)
{
	CString strLog;
	CString m_strTime = GetTime();
	strLog.Format(_T("%s\r\n%s\r\n"),m_strTime,m_strLog);
	m_ServerLog += strLog;
	m_editLog.SetWindowTextW(m_ServerLog);
	m_editLog.LineScroll(m_editLog.GetLineCount());		// 当服务器有新消息时，光标自动移动到最后一行
}


void CServerLogDlg::OnBnClickedButtonServerOff()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pMainDlg->ServerOff();
	GetDlgItem(IDC_BUTTON_SERVERON)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SERVEROFF)->EnableWindow(FALSE);
}


BOOL CServerLogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetDlgItem(IDC_BUTTON_SERVEROFF)->EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CServerLogDlg::OnBnClickedButtonSavelog()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pMainDlg->SaveLog();
}
