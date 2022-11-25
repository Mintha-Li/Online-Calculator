
// ServerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Server.h"
#include "ServerDlg.h"
#include "afxdialogex.h"
#include "SocketListen.h"
#include "SocketServer.h"
#include "SetUpDlg.h"
#include "UserManagerDlg.h"
#include "ServerLogDlg.h"
#include "InfoFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CServerDlg 对话框



CServerDlg::CServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SERVER_DIALOG, pParent)
{
	CServerLogDlg m_ServerLogDlg(this);
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_ptrListen = NULL;
}

CServerDlg::~CServerDlg()
{
	//if(m_ptrListen!=nullptr)
	//	delete m_ptrListen;
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MAIN, m_TabMain);
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CServerDlg::OnTcnSelchangeTabMain)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CServerDlg 消息处理程序

BOOL CServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	InitUserData(); //初始化用户数据
	InitTabMain();	//初始化Tab界面

	//测试用
	//m_file->ReadUserData();
	//m_ServerLogDlg->AddServerLog(m_file->userlist.back().userName);
	//m_file->AddUser((CString)"龙哥", (CString)"123", 123);
	//m_file->WriteUserData();
	//m_file->ReadUserData();
	//m_ServerLogDlg->AddServerLog(m_file->userlist.back().userName);
	//m_file->WriteUserData();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//监听套接字初始化函数
void CServerDlg::InitSocketListen()
{
	CString strMsg;

	m_ptrListen = new CSocketListen(this);
	if (m_ptrListen == NULL)
	{
		strMsg.Format(L"初始化失败.错误码:%d", GetLastError());
		MessageBox(strMsg, L"提示", MB_OK | MB_ICONERROR);
	}
	// 创建套接字
	// TCP:SOCK_STREAM
	// UDP:SOCK_DGRAM
	if (m_ptrListen->Create(m_Port, SOCK_STREAM,m_IPAddress) == FALSE)
	{
		strMsg.Format(L"初始化失败.错误码:%d", GetLastError());
		MessageBox(strMsg, L"提示", MB_OK | MB_ICONERROR);
	}

	// 将套接字设置为监听模式
	if (m_ptrListen->Listen() == FALSE)
	{
		strMsg.Format(L"初始化失败.错误码:%d", GetLastError());
		MessageBox(strMsg, L"提示", MB_OK | MB_ICONERROR);
	}

}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CServerDlg::OnAccept()
{
	//返回一个建立连接的套接字
	CSocketServer* pSocket = new CSocketServer(this);
	if (m_ptrListen->Accept(*pSocket) == FALSE)
	{
		delete pSocket;
	}
	else
	{
		//将客户端的IP地址显示到服务器界面上
		CString strIPAddress;
		UINT uPort;
		pSocket->GetPeerName(strIPAddress, uPort);
		//显示信息
		CString strLog;
		strLog.Format(L"有客户端连接，IP地址:%s,端口号:%d", strIPAddress,uPort);
		m_ServerLogDlg->AddServerLog(strLog);
	}
}

//服务器开启
BOOL CServerDlg::ServerOn()
{
	m_IPAddress = m_SetUpDlg->m_IPAddress;		//从设置面板获取IP与端口号
	m_Port = m_SetUpDlg->m_Port;
	InitSocketListen();
	CString strLog;
	strLog.Format(L"服务器启动，运行IP地址:%s:%d",m_IPAddress,m_Port);
	m_ServerLogDlg->AddServerLog(strLog);
	m_SetUpDlg->m_editCost.EnableWindow(FALSE);
	return 0;
}

//服务器关闭
BOOL CServerDlg::ServerOff()
{
	delete m_ptrListen;
	CString strLog;
	strLog.Format(L"服务器已关闭");
	m_ServerLogDlg->AddServerLog(strLog);
	m_SetUpDlg->m_editCost.EnableWindow(TRUE);
	return 0;
}

//保存日志
void CServerDlg::SaveLog()
{
	m_UserData->WriteLog(m_ServerLogDlg->m_ServerLog);
}

//Tab界面初始化
void CServerDlg::InitTabMain()
{
	m_TabMain.InsertItem(0, _T("服务器日志"));
	m_TabMain.InsertItem(1, _T("用户管理"));
	m_TabMain.InsertItem(2, _T("服务器设置"));
	m_ServerLogDlg = new CServerLogDlg(this);
	m_UserMGMTDlg = new CUserManagerDlg(this);
	m_SetUpDlg = new CSetUpDlg(this);

	m_ServerLogDlg->Create(IDD_SERVERLOG, &m_TabMain);
	m_UserMGMTDlg->Create(IDD_USER_MANAGER, &m_TabMain);
	m_SetUpDlg->Create(IDD_SETUP, &m_TabMain);


	CRect rc;
	m_TabMain.GetClientRect(rc);
	rc.top += 30;
	rc.bottom -= 0;
	rc.left += 0;
	rc.right -= 0;
	m_ServerLogDlg->MoveWindow(&rc);
	m_UserMGMTDlg->MoveWindow(&rc);
	m_SetUpDlg->MoveWindow(&rc);

	pDialog[0] = m_ServerLogDlg;
	pDialog[1] = m_UserMGMTDlg;
	pDialog[2] = m_SetUpDlg;

	pDialog[0]->ShowWindow(SW_SHOW);
	pDialog[1]->ShowWindow(SW_HIDE);
	pDialog[2]->ShowWindow(SW_HIDE);

	m_CurSelTab = 0;
}

void CServerDlg::OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);
	m_CurSelTab = m_TabMain.GetCurSel();
	pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);

	*pResult = 0;
}


void CServerDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (MessageBox(L"请确认已经将所有更改保存!", L"确认退出?",MB_ICONWARNING|MB_OKCANCEL) == IDOK) {
		CDialogEx::OnClose();
	}
	else {
		return;
	}
}

//用户数据初始化函数
void CServerDlg::InitUserData()
{
	m_UserData = new CInfoFile;
	if (m_UserData->IsFileExisted() == FALSE)
	{
		m_UserData->CreateUserData();
	}
	m_UserData->ReadUserData();
}



