#pragma once

// CSocketListen 命令目标
class CServerDlg;
class CSocketListen : public CSocket
{
private:
	CServerDlg* m_pMainDlg;
public:
	CSocketListen(CServerDlg* pDlg);
	virtual ~CSocketListen();
	virtual void OnAccept(int nErrorCode);
};