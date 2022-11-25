// UserManagerDlg.cpp: 实现文件
//

#include "pch.h"
#include "Server.h"
#include "afxdialogex.h"
#include "UserManagerDlg.h"
#include "InfoFile.h"
#include "ServerDlg.h"


// CUserManagerDlg 对话框

IMPLEMENT_DYNAMIC(CUserManagerDlg, CDialogEx)

CUserManagerDlg::CUserManagerDlg(CServerDlg* pDlg, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_USER_MANAGER, pParent)
{
	m_pMainDlg = pDlg;
	m_pUserData = m_pMainDlg->m_UserData;
}

CUserManagerDlg::~CUserManagerDlg()
{
}

void CUserManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DATA, m_UserDataList);
	DDX_Control(pDX, IDC_EDIT_ACCOUNT, m_editAccount);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_editPassword);
	DDX_Control(pDX, IDC_EDIT_VALUE, m_editValue);
}


BEGIN_MESSAGE_MAP(CUserManagerDlg, CDialogEx)

	ON_BN_CLICKED(IDC_BUTTON_DEL_USER, &CUserManagerDlg::OnBnClickedButtonDelUser)
	ON_BN_CLICKED(IDC_BUTTON_ADDUSER, &CUserManagerDlg::OnBnClickedButtonAdduser)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CUserManagerDlg::OnBnClickedButtonSave)
END_MESSAGE_MAP()


// CUserManagerDlg 消息处理程序


BOOL CUserManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_UserDataList.ModifyStyle(0, LVS_REPORT);
	m_UserDataList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_HEADERINALLVIEWS | LVS_EX_FULLROWSELECT);
	//绘制网格线，表头不可以拖拽，可以选择整行或者整列
	CString col[3] = { _T("用户名"),_T("密码"),_T("余额") };
	RECT r;
	m_UserDataList.GetClientRect(&r);
	for (int i = 0; i < 3; i++) {
		m_UserDataList.InsertColumn(i, col[i], LVCFMT_LEFT,r.right / 3);	//插入表头
	}
	
	//背景与文字主题设置(测试用)
	//dataList.SetBkColor(RGB(100, 120, 200));
	//dataList.SetTextColor(RGB(200, 120, 300));
	//dataList.SetTextBkColor(RGB(200, 200, 300));

	UpdateListData();		//从链表中更新列表数据

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

//从链表中更新列表数据
void CUserManagerDlg::UpdateListData(BOOL status)
{
	//若status为TRUE，则将链表中的信息读取到列表，默认为TRUE
	if (status==TRUE)
	{
		m_UserDataList.DeleteAllItems();  //清空列表所有数据
		int i = 0;
		for (list<User>::iterator user = m_pUserData->userlist.begin(); user != m_pUserData->userlist.end(); user++)
		{
			m_UserDataList.InsertItem(i, user->userName);				//按用户名插入新的一行
			int column = 1;
			m_UserDataList.SetItemText(i, column++, user->password);	//设置密码列
			CString value;
			value.Format(L"%.2f", user->value);							//转换余额为文本
			m_UserDataList.SetItemText(i, column++, value);				//设置余额列
			i++;
		}
	}
	//若status为FALSE，则将链表中的信息存到硬盘
	else
	{
		m_pUserData->WriteUserData();
	}

}

//删除用户（可以多行删除）
void CUserManagerDlg::OnBnClickedButtonDelUser()
{
	// TODO: 在此添加控件通知处理程序代码
	if (MessageBox(L"确认删除？", L"删除用户", MB_YESNO | MB_ICONWARNING) == IDYES) 
	{
		POSITION pos = m_UserDataList.GetFirstSelectedItemPosition();
		while (pos)
		{
			int nIndex = m_UserDataList.GetNextSelectedItem(pos);
			CString username;
			username = m_UserDataList.GetItemText(nIndex, 1);		//获取要删除的用户名
			m_pUserData->DeleteUser(username);						//删除链表中的用户信息
			m_UserDataList.DeleteItem(nIndex);						//删除列表中的用户信息
			pos = m_UserDataList.GetFirstSelectedItemPosition();
		}
	}
	else 
	{
		return;	//用户取消
	}
}

//添加用户
void CUserManagerDlg::OnBnClickedButtonAdduser()
{
	// TODO: 在此添加控件通知处理程序代码
	CString username;
	CString password;
	CString value;
	m_editAccount.GetWindowTextW(username);					//从编辑框中获取用户名
	m_editPassword.GetWindowTextW(password);				//从编辑框中获取密码
	m_editValue.GetWindowTextW(value);
	m_pUserData->AddUser(username, password, _ttof(value));	//从编辑框中获取余额并转换为浮点型
	UpdateListData();
}

//保存更改
void CUserManagerDlg::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pUserData->WriteUserData();
	MessageBox(L"用户信息已保存", L"提示",MB_ICONINFORMATION);
}
