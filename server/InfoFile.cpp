#include "pch.h"
#include "InfoFile.h"

CInfoFile::CInfoFile()
{
}


CInfoFile::~CInfoFile()
{
}

void CInfoFile::ReadUserData()
{
	ifstream ifs(_F_USERDATA);//输入方式打开文件
	char str[1024] = { 0 };
	char *buf;
	num = 0;//初始化用户数目为0
	userlist.clear();
	//取出表头
	ifs.getline(str, sizeof(str));

	while (!ifs.eof())//没到文件结尾
	{
		User tmp;

		ifs.getline(str, sizeof(str));//读取一行
		num++;//用户数目+1

		char *strtemp = strtok_s(str, "|", &buf);//以“|”切割
		if (strtemp != NULL)
		{
			tmp.userName = (CString)strtemp;//用户名
		}
		else
		{
			break;
		}
		strtemp = strtok_s(NULL, "|", &buf);
		tmp.password = (CString)strtemp;	//密码

		strtemp = strtok_s(NULL, "|", &buf);
		tmp.value = atoi(strtemp);			//余额

		userlist.push_back(tmp);			//放在链表后面
	}
	ifs.close();
}

void CInfoFile::WriteUserData()
{
	ofstream ofs(_F_USERDATA);//输出方式打开文件

	if (userlist.size() > 0)	//用户链表有内容才执行
	{
		ofs << "用户名|密码|余额" << endl; //写入表头

		//通过迭代器取出链表内容，写入文件，以“|”分隔，结尾加换行
		for (list<User>::iterator user = userlist.begin(); user != userlist.end(); user++)
		{
			ofs << (CStringA)user->userName << "|";
			ofs << (CStringA)user->password << "|";
			ofs << user->value << endl;
		}
	}
	else if (userlist.size() == 0) {
		ofs << "用户名|密码|余额" << endl; //表为空，仅写入表头
	}

	ofs.close();//关闭文件
}

BOOL CInfoFile::IsFileExisted()
{
	if (!PathIsDirectory(_T(_D_DATA))) //目录不存在
	{
		CreateDirectory(_T(_D_DATA), NULL);//不存在则创建
		return FALSE;
	}
	if (!PathFileExists(_T(_F_USERDATA)))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CInfoFile::IsUserExisted(CString username)
{
	for (list<User>::iterator user = userlist.begin(); user != userlist.end(); user++)
	{
		if (user->userName == username) {
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CInfoFile::IsUserCorrect(CString username, CString password)
{
	for (list<User>::iterator user = userlist.begin(); user != userlist.end(); user++)
	{
		if (user->userName == username)
		{
			if (user->password == password) {
				return TRUE;
			}
			else {
				return FALSE;
			}
		}
	}
	return FALSE;
}

void CInfoFile::CreateUserData()
{
	ofstream ofs(_F_USERDATA);	//输出方式打开文件
	ofs << "用户名|密码|余额" << endl; //写入表头
	ofs << "admin|admin|0" << endl; //写入表头
	ofs.close();
}

void CInfoFile::WriteLog(CString log)
{
	ofstream ofs(_F_LOG);		//输出方式打开文件
	if (log.IsEmpty() == FALSE)	//有内容才执行
	{
		ofs.write((CStringA)log, ((CStringA)log).GetLength());
	}
	ofs.close();//关闭文件
}

void CInfoFile::AddUser(CString userName, CString password, DOUBLE value)
{
	User tmp;

	if (!userName.IsEmpty() && !password.IsEmpty() && value >= 0)
	{
		tmp.userName = userName;
		tmp.password = password;
		tmp.value = value;

		userlist.push_back(tmp);	//放在链表的后面
	}
}

void CInfoFile::DeleteUser(CString userName)
{
	if (userlist.size() > 0)
	{
		for (list<User>::iterator user = userlist.begin(); user != userlist.end(); user++)
		{
			if (user->userName == userName) {
				userlist.erase(user);
				num--;
				break;
			}
		}
	}
}

User CInfoFile::GetUser(CString username)
{
	for (list<User>::iterator  user = userlist.begin(); user != userlist.end(); user++)
	{
		if (user->userName == username) {
			return *user;
		}
	}
}

DOUBLE CInfoFile::GetUserValue(CString username)
{
	for (list<User>::iterator user = userlist.begin(); ; user++)
	{
		if (user->userName == username) {
			return user->value;
			break;
		}
	}
}

BOOL CInfoFile::ChangeUserValue(CString username, DOUBLE newValue)
{
	if (newValue >= 0) {
		for (list<User>::iterator user = userlist.begin(); ; user++)
		{
			if (user->userName == username) {
				user->value = newValue;
				break;
			}
		}
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	
}


BOOL CInfoFile::ChangePassword(CString username, CString newPassword)
{
	for (list<User>::iterator user = userlist.begin(); ; user++)
	{
		if (user->userName == username) {
			user->password = newPassword;
			break;
		}
	}
	return TRUE;
}

