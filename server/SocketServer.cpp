// SocketServer.cpp: 实现文件
//

#include "pch.h"
#include "Server.h"
#include "SocketServer.h"
#include "ServerDlg.h"
#include "ServerLogDlg.h"
#include "UserManagerDlg.h"
#include "InfoFile.h"


// CSocketServer

CSocketServer::CSocketServer()
{
}

CSocketServer::CSocketServer(CServerDlg * pDlg)
{
	pMainDlg = pDlg;
	pLogDlg = pMainDlg->m_ServerLogDlg;
	pUserData = pMainDlg->m_UserData;
}

CSocketServer::~CSocketServer()
{
}


// CSocketServer 成员函数

void CSocketServer::OnReceive(int nErrorCode)
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

//消息处理函数
//备注：标准消息格式：
//|请求(4位)|状态值(4位)|用户名长度(2位)|密码[校验码]长度(2位)|用户名(由前面确定)|
//	密码[校验码](由前面确定)|发送信息|
//举例：用户admin尝试登录,密码为admin
//消息格式为：REQUEST_LOGIN+STATUS_NONE+05+05+admin+admin
void CSocketServer::MsgProc(CString strMsg)
{
	UINT m_Request;
	UINT m_Status;
	CString m_UserName;
	CString m_CheckNum;
	UINT userNameLen;
	UINT passwordLen;
	CString m_Text;
	CString m_Log;
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
		m_Log.Format(L"用户%s,发送数据：%s", m_UserName, strMsg);
		pLogDlg->AddServerLog(m_Log);
		break;
	}
	case REQUEST_LOGIN: {
		if (pUserData->IsUserCorrect(m_UserName, m_CheckNum) == TRUE) {
			CString strValue;
			strValue.Format(L"%.2f", pUserData->GetUserValue(m_UserName));
			MsgSend(m_UserName, m_CheckNum, strValue, REQUEST_LOGIN, STATUS_TRUE);
		}
		else {
			MsgSend(m_UserName, m_CheckNum, L"0", REQUEST_LOGIN, STATUS_FALSE);
		}
		break;
	};
	case REQUEST_REGISTER: {
		if (pUserData->IsUserExisted(m_UserName) == FALSE) {
			pMainDlg->m_UserData->AddUser(m_UserName, m_CheckNum, 0);
			pMainDlg->m_UserMGMTDlg->UpdateListData();
			MsgSend(m_UserName, m_CheckNum, L"0", REQUEST_REGISTER, STATUS_TRUE);
		}
		else {
			MsgSend(m_UserName, m_CheckNum, L"0", REQUEST_REGISTER, STATUS_FALSE);
		}
		break;
	};
	case REQUEST_CALCULATE: {
		CString textbuf = m_Text;
		vector<CString> m_InputNum;
		Operation(textbuf, m_InputNum);
		DOUBLE m_Result = Calculation(m_InputNum);
		CString strResult;
		strResult.Format(L"%.2f", m_Result);
		CString strLog;
		strLog.Format(L"用户:%s,计算算式:%s", m_UserName, m_Text);
		pLogDlg->AddServerLog(strLog);
		MsgSend(m_UserName, m_CheckNum, strResult, REQUEST_CALCULATE, STATUS_TRUE);
		break;
	}
	case REQUEST_CHARGE: {
		DOUBLE valCharge = _ttof(m_Text);
		if (pUserData->IsUserCorrect(m_UserName, m_CheckNum) && (valCharge > 0))
		{
			DOUBLE userVal;
			userVal = pUserData->GetUserValue(m_UserName);
			userVal += valCharge;
			pUserData->ChangeUserValue(m_UserName, userVal);
			pMainDlg->m_UserMGMTDlg->UpdateListData();
			CString strChargeVal;
			strChargeVal.Format(L"%.2f", valCharge);
			MsgSend(m_UserName, m_CheckNum, strChargeVal, REQUEST_CHARGE, STATUS_TRUE);
		}
		else
		{
			MsgSend(m_UserName, m_CheckNum, L"0", REQUEST_CHARGE, STATUS_FALSE);
		}
		break;
	}
	default:
		break;
	}
}

//标准化消息生成生成函数
BOOL CSocketServer::MsgGenerator(char szBuf[], CString userName, CString userPassword, CString textSend, UINT nRequest, UINT nStatus)
{
	USES_CONVERSION;
	CString strMsg;
	UINT userNameLen = userName.GetLength();
	CString strUserNameLen;
	if (userNameLen > 0 && userNameLen < 9) {
		strUserNameLen.Format(L"0%d", userNameLen);
	}
	else
	{
		strUserNameLen.Format(L"%d", userNameLen);
	}
	UINT PasswordLen = userPassword.GetLength();
	CString strPasswordLen;
	if (PasswordLen > 0 && PasswordLen < 9) {
		strPasswordLen.Format(L"0%d", PasswordLen);
	}
	else
	{
		strPasswordLen.Format(L"%d", PasswordLen);
	}
	strMsg.Format(L"%d%d%s%s%s%s%s", nRequest, nStatus, strUserNameLen, strPasswordLen, userName, userPassword, textSend);
	strcpy_s(szBuf, MAX_BUF, T2A(strMsg));
	return TRUE;
}

//消息发送与日志记录函数
void CSocketServer::MsgSend(CString username, CString userPassword, CString textSend, UINT nRequest, UINT nStatus)
{
	char szBuf[MAX_BUF] = { "0" };
	MsgGenerator(szBuf, username, userPassword, textSend, nRequest, nStatus);
	Send(szBuf, MAX_BUF);
	CString m_Log;
	CString strRequest;
	CString strStatus;
	CString strNotes;
	switch (nRequest)
	{
	case REQUEST_NONE:
	{
		strRequest = L"测试"; break;
	}
	case REQUEST_LOGIN:
	{
		strRequest = L"登录"; break;
	}
	case REQUEST_REGISTER:
	{
		strRequest = L"注册"; break;
	}
	case REQUEST_CHARGE:
	{
		strRequest = L"充值"; break;
	}
	case REQUEST_CALCULATE:
	{
		strRequest = L"计算"; break;
	}
	default:
		break;
	}

	switch (nStatus)
	{
	case STATUS_TRUE:
	{
		strStatus = L"成功"; break;
	}
	case STATUS_FALSE:
	{
		strStatus = L"失败"; break;
	}
	case STATUS_NONE:
	{
		strRequest = L"未定义"; break;
	}
	default:
		break;
	}
	m_Log.Format(L"用户%s,尝试%s;状态:%s", username, strRequest, strStatus);
	if (nRequest == REQUEST_CHARGE && nStatus == STATUS_TRUE) {
		strNotes.Format(L";充值金额:+%.2f", _ttof(textSend));
		m_Log.Append(strNotes);
	}
	else if (nRequest == REQUEST_CALCULATE && nStatus == STATUS_TRUE) {
		strNotes.Format(L";结果:%.2f", _ttof(textSend));
		m_Log.Append(strNotes);
	}
	pLogDlg->AddServerLog(m_Log);
}

//判断是否为运算符
BOOL CSocketServer::IsOpr(wchar_t c)
{
	for (int i = 0; i < LPCT_OPCH.GetLength(); i++)
	{
		if (c == LPCT_OPCH[i]) {
			return TRUE;
		}
	}
	return FALSE;
}


BOOL CSocketServer::IsOpr(CString str)
{
	for (int i = 0; i < LPCT_OPCH.GetLength(); i++)
	{
		if (str == LPCT_OPCH[i]) {
			return TRUE;
		}
	}
	return FALSE;
}

//运算符转换函数
INT CSocketServer::OperatorConvert(CString opr)
{
	if (L'+' == opr)
	{
		return PLUS;
	}
	else if (L'-' == opr)
	{
		return MINUS;
	}
	else if (L'*' == opr)
	{
		return MULTIPLY;
	}
	else if (L'/' == opr)
	{
		return DIVIDE;
	}
	else
	{
		return -1;
	}
}

//中缀表达式转后缀（逆波兰）表达式
void CSocketServer::Operation(CString TBuff, vector<CString>& m_InputNum)
{
	INT i = 0;
	INT length = TBuff.GetLength();
	stack<wchar_t> stack1; //存放运算符的栈
	CString StrNum = L"";
	CString Strck;
	for (INT i = 0; i <= length; i++)
	{
		if ((TBuff[i] - '0') >= 0 && (TBuff[i] - '0') <= 9 || (TBuff[i] == '.'))
		{
			StrNum += TBuff[i];
			continue;
		}

		//遇到其他字符,即当前数字结束，此时将数字保存到vector
		if (!StrNum.IsEmpty()) {
			m_InputNum.push_back(StrNum);
			StrNum = "";
		}

		if (TBuff[i] == '(')
		{
			stack1.push(TBuff[i]);	//左括号无条件进栈
			continue;
		}
		else if (TBuff[i] == ')')
		{
			while (stack1.top() != '(')
			{
				if (stack1.empty()) //基于安全性的考虑
				{
					AfxMessageBox(L"提示:括号不匹配！");
					ASSERT(stack1.empty());
				}
				Strck = stack1.top();
				m_InputNum.push_back(Strck);
				stack1.pop();
			}
			stack1.pop();	//将'('从栈中弹出
			continue;
		}
		else if (IsOpr(TBuff[i]))
		{
			//如果栈空，直接进栈
			if (stack1.empty())
			{
				stack1.push(TBuff[i]);
				continue;
			}
			//如果操作符优先级比栈顶操作符优先级高，入栈
			if (GetPriority(TBuff[i]) > GetPriority(stack1.top()))
			{
				stack1.push(TBuff[i]);
				continue;
			}
			//如果操作符优先级比栈顶操作符优先级低
			else
			{
				while (1)
				{
					//栈顶操作符进入vector
					Strck = stack1.top();
					m_InputNum.push_back(Strck);
					stack1.pop();

					//继续判断优先级
					//栈为空，入栈，退出循环
					if (stack1.empty())
					{
						stack1.push(TBuff[i]);
						break;
					}

					//操作符优先级比栈顶操作符优先级高，入栈，退出循环
					else if (GetPriority(TBuff[i]) > GetPriority(stack1.top()))
					{
						stack1.push(TBuff[i]);
						break;
					}
				}
				continue;
			}
		}
	}
	//将栈中的操作符压进vector
	while (!stack1.empty())
	{
		Strck = stack1.top();
		m_InputNum.push_back(Strck);
		stack1.pop();
	}
	return;
}

//后缀表达式计算结果
DOUBLE CSocketServer::Calculation(vector<CString> m_InputNum)
{
	INT i = 0;
	INT length = (INT)m_InputNum.size();
	stack<DOUBLE> temp; //用来存放数字的栈
	DOUBLE sum = 0;
	DOUBLE firstNum, secondNum;
	while (i < length)
	{
		//如果是数字，转成DOUBLE压进数字栈
		if (!IsOpr(m_InputNum[i]))
		{
			temp.push(_ttof(m_InputNum[i]));
		}
		//如果是运算符
		else if (IsOpr(m_InputNum[i]))
		{
			firstNum = temp.top();
			temp.pop();
			secondNum = temp.top();
			temp.pop();
			switch (OperatorConvert(m_InputNum[i]))
			{
			case PLUS:
				sum = firstNum + secondNum;
				break;
			case MINUS:
				sum = secondNum - firstNum;
				break;
			case MULTIPLY:
				sum = firstNum * secondNum;
				break;
			case DIVIDE:
				sum = secondNum / firstNum;
				break;
			}
			temp.push(sum);
		}
		i++;
	}
	return temp.top();
}

//获取运算符优先级
INT CSocketServer::GetPriority(wchar_t ptr)
{
	switch (ptr)
	{
	case '+': return 1;
	case '-': return 1;
	case '*': return 2;
	case '/': return 2;
	default: return 0;
	}
}
