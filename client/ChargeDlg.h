#pragma once
#include "NumEdit.h"

class CClientDlg;
// CChargeDlg 对话框

class CChargeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChargeDlg)

public:
	CChargeDlg(CClientDlg *pDlg,CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CChargeDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHARGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CNumEdit m_editChargeValue;
	DOUBLE m_valCharge;
	afx_msg void OnBnClickedButtonChargeOk();
	void RefreshUserVal();
private:
	CClientDlg *pMainDlg;
public:
	CStatic m_staticTitle;
	CFont staticTitleFont;
};