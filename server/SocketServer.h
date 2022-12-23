#pragma once
#include <stack>
#include <vector>
#include <cmath>

using namespace std;
const CString LPCT_OPCH = L"+-*/^";	//保存运算符

// CSocketServer 命令目标
class CServerDlg;
class CServerLogDlg;
class CInfoFile;
class CSocketServer : public CSocket
{
private:
	CServerDlg *pMainDlg;
	CServerLogDlg *pLogDlg;
	CInfoFile *pUserData;
public:
	CSocketServer();
	CSocketServer(CServerDlg* pDlg);
	virtual ~CSocketServer();
	virtual void OnReceive(int nErrorCode);
public:
	void MsgProc(CString strMsg);
	BOOL MsgGenerator(char szBuf[], CString userName, CString userPassword, CString textSend,
		UINT nRequest = REQUEST_NONE, UINT nStatus = STATUS_NONE);
	void MsgSend(CString username, CString userPassword, CString textSend = L"0",
		UINT nRequest = REQUEST_NONE, UINT nStatus = STATUS_NONE);
public:
	BOOL IsOpr(wchar_t c);
	BOOL IsOpr(CString str);
	INT OperatorConvert(CString opr);
	void Operation(CString TBuff, vector<CString> & m_InputNum);
	DOUBLE Calculation(vector<CString> m_InputNum);
	INT GetPriority(wchar_t ptr);
public:
	DOUBLE valCost;
};
