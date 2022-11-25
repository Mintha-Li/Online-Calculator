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
	ifstream ifs(_F_USERDATA);//���뷽ʽ���ļ�
	char str[1024] = { 0 };
	char *buf;
	num = 0;//��ʼ���û���ĿΪ0
	userlist.clear();
	//ȡ����ͷ
	ifs.getline(str, sizeof(str));

	while (!ifs.eof())//û���ļ���β
	{
		User tmp;

		ifs.getline(str, sizeof(str));//��ȡһ��
		num++;//�û���Ŀ+1

		char *strtemp = strtok_s(str, "|", &buf);//�ԡ�|���и�
		if (strtemp != NULL)
		{
			tmp.userName = (CString)strtemp;//�û���
		}
		else
		{
			break;
		}
		strtemp = strtok_s(NULL, "|", &buf);
		tmp.password = (CString)strtemp;	//����

		strtemp = strtok_s(NULL, "|", &buf);
		tmp.value = atoi(strtemp);			//���

		userlist.push_back(tmp);			//�����������
	}
	ifs.close();
}

void CInfoFile::WriteUserData()
{
	ofstream ofs(_F_USERDATA);//�����ʽ���ļ�

	if (userlist.size() > 0)	//�û����������ݲ�ִ��
	{
		ofs << "�û���|����|���" << endl; //д���ͷ

		//ͨ��������ȡ���������ݣ�д���ļ����ԡ�|���ָ�����β�ӻ���
		for (list<User>::iterator user = userlist.begin(); user != userlist.end(); user++)
		{
			ofs << (CStringA)user->userName << "|";
			ofs << (CStringA)user->password << "|";
			ofs << user->value << endl;
		}
	}
	else if (userlist.size() == 0) {
		ofs << "�û���|����|���" << endl; //��Ϊ�գ���д���ͷ
	}

	ofs.close();//�ر��ļ�
}

BOOL CInfoFile::IsFileExisted()
{
	if (!PathIsDirectory(_T(_D_DATA))) //Ŀ¼������
	{
		CreateDirectory(_T(_D_DATA), NULL);//�������򴴽�
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
	ofstream ofs(_F_USERDATA);	//�����ʽ���ļ�
	ofs << "�û���|����|���" << endl; //д���ͷ
	ofs << "admin|admin|0" << endl; //д���ͷ
	ofs.close();
}

void CInfoFile::WriteLog(CString log)
{
	ofstream ofs(_F_LOG);		//�����ʽ���ļ�
	if (log.IsEmpty() == FALSE)	//�����ݲ�ִ��
	{
		ofs.write((CStringA)log, ((CStringA)log).GetLength());
	}
	ofs.close();//�ر��ļ�
}

void CInfoFile::AddUser(CString userName, CString password, DOUBLE value)
{
	User tmp;

	if (!userName.IsEmpty() && !password.IsEmpty() && value >= 0)
	{
		tmp.userName = userName;
		tmp.password = password;
		tmp.value = value;

		userlist.push_back(tmp);	//��������ĺ���
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

