// SetUp.cpp: 实现文件
//

#include "pch.h"
#include "client.h"
#include "SetUp.h"
#include "afxdialogex.h"


// CSetUp 对话框

IMPLEMENT_DYNAMIC(CSetUp, CDialogEx)

CSetUp::CSetUp(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETUP, pParent)
{

}

CSetUp::~CSetUp()
{
}

void CSetUp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetUp, CDialogEx)
END_MESSAGE_MAP()


// CSetUp 消息处理程序
