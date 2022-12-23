#pragma once
#include <list>
#include <fstream>
#include <iostream>

using namespace std;

#define _D_DATA "./data/"
#define _F_USERDATA "./data/userdata.lib"
#define _F_LOG "./data/serverlog.log"
#define _F_CONFIG L"./data/config.ini"

struct User
{
	CString userName;
	CString password;
	DOUBLE value;
};

class CInfoFile
{
public:
	CInfoFile();
	~CInfoFile();
public:
	void ReadUserData();
	void WriteUserData();
	BOOL IsFileExisted();
public:
	BOOL IsUserExisted(CString username);
	BOOL IsUserCorrect(CString username, CString password);
	void CreateUserData();
	void AddUser(CString userName,CString password,DOUBLE value);
	void DeleteUser(CString userName);
	User GetUser(CString username);
	DOUBLE GetUserValue(CString username);
	BOOL ChangeUserValue(CString username,DOUBLE newValue);
	BOOL ChangePassword(CString username, CString newPassword);
public:
	void WriteLog(CString log);
public:
	list<User> userlist;
	int num;
};
