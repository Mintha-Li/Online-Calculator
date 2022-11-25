// SocketClient.cpp: 实现文件
//

#include "pch.h"
#include "Client.h"
#include "SocketClient.h"
#include "ClientDlg.h"
#include "LoginDlg.h"
// CSocketClient

CSocketClient::CSocketClient(CClientDlg *pDlg)
{
	pMainDlg = pDlg;
}

CSocketClient::~CSocketClient()
{
}


// CSocketClient 成员函数


void CSocketClient::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CSocket::OnClose(nErrorCode);
}


void CSocketClient::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	CString strMsg;
	char szMsg[MAX_BUF] = { 0 };
	int iRead = Receive(szMsg, MAX_BUF, 0);
	if (iRead > 0)
	{
		strMsg = szMsg;
		MsgProc(strMsg);
	}
	CSocket::OnReceive(nErrorCode);
}

void CSocketClient::MsgProc(CString strMsg)
{

	UINT m_Request;
	UINT m_Status;
	CString m_UserName;
	CString m_CheckNum;
	UINT userNameLen;
	UINT passwordLen;
	CString m_Text;
	m_Request = _ttoi(strMsg.Left(4));
	m_Status = _ttoi(strMsg.Mid(4, 4));
	userNameLen = _ttoi(strMsg.Mid(8, 2));
	passwordLen = _ttoi(strMsg.Mid(10, 2));
	m_UserName = strMsg.Mid(12, userNameLen);
	m_CheckNum = strMsg.Mid(12 + userNameLen, passwordLen);
	m_Text = strMsg.Mid(12 + userNameLen + passwordLen);
	switch (m_Request)
	{
	case REQUEST_NONE: {
		break;
	}
	case REQUEST_LOGIN: {
		if (m_Status == STATUS_TRUE) {
			pMainDlg->OnLoginSuccess();
			pMainDlg->m_value = m_Text;
		}
		else {
			pMainDlg->OnLoginFail();
		}
		break;
	};
	case REQUEST_REGISTER: {
		if (m_Status == STATUS_TRUE) {
			pMainDlg->OnRegisterSuccess();
		}
		else {
			pMainDlg->OnRegisterFail();
		}
		break;
	};
	case REQUEST_CALCULATE: {
		if (m_Status == STATUS_TRUE) {
			pMainDlg->OnCalculateSuccess(m_Text);
		}
		break;
	}
	case REQUEST_CHARGE: {
		if (m_Status == STATUS_TRUE) {
			pMainDlg->OnChargeSuccess(_ttof(m_Text));
		}
		else {
			//pMainDlg->OnChargeFail();
		}
		break;
	}
	default:
		break;
	}
}
