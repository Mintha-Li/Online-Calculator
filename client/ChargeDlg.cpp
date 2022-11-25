// ChargeDlg.cpp: 实现文件
//

#include "pch.h"
#include "Client.h"
#include "ChargeDlg.h"
#include "afxdialogex.h"
#include "ClientDlg.h"


// CChargeDlg 对话框

IMPLEMENT_DYNAMIC(CChargeDlg, CDialogEx)

CChargeDlg::CChargeDlg(CClientDlg* pDlg,CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHARGE, pParent)
{
	pMainDlg = pDlg;
}

CChargeDlg::~CChargeDlg()
{
}

void CChargeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_CGVALUE, m_editChargeValue);
	DDX_Control(pDX, IDC_STATIC_TITLE, m_staticTitle);
}


BEGIN_MESSAGE_MAP(CChargeDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CHARGE_OK, &CChargeDlg::OnBnClickedButtonChargeOk)
END_MESSAGE_MAP()


// CChargeDlg 消息处理程序

BOOL CChargeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_editChargeValue.setRange(double(0), double(9999));
	SetDlgItemText(IDC_EDIT_ACCOUNT, pMainDlg->m_account);
	SetDlgItemText(IDC_EDIT_VALUE, pMainDlg->m_value);
	
	//设置字体:楷体;字号:150
	staticTitleFont.CreatePointFont(150, _T("楷体"));
	m_staticTitle.SetFont(&staticTitleFont);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CChargeDlg::OnBnClickedButtonChargeOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString m_strChargeVal;
	m_editChargeValue.GetWindowTextW(m_strChargeVal);
	m_valCharge = _ttof(m_strChargeVal);
	pMainDlg->ChargeVal(m_valCharge);
}

void CChargeDlg::RefreshUserVal()
{
	SetDlgItemText(IDC_EDIT_VALUE, pMainDlg->m_value);
}
