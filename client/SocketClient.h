#pragma once
class CClientDlg;
// CSocketClient 命令目标
class CSocketClient : public CSocket
{
public:
	CSocketClient(CClientDlg *pDlg);
	virtual ~CSocketClient();
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	void MsgProc(CString strMsg);
private:
	CClientDlg *pMainDlg;
};


