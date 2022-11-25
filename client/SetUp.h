#pragma once


// CSetUp 对话框

class CSetUp : public CDialogEx
{
	DECLARE_DYNAMIC(CSetUp)

public:
	CSetUp(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSetUp();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETUP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
