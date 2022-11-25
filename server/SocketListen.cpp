// CSocketListen.cpp: 实现文件

#include "pch.h"
#include "Server.h"
#include "ServerDlg.h"
#include "SocketListen.h"


// CSocketListen

CSocketListen::CSocketListen(CServerDlg *pDlg)
{
	m_pMainDlg = pDlg;
}

CSocketListen::~CSocketListen()
{
}


// CSocketListen 成员函数


void CSocketListen::OnAccept(int nErrorCode)
{
	m_pMainDlg->OnAccept();
	CSocket::OnAccept(nErrorCode);
}
