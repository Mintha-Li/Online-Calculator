// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

// 添加要在此处预编译的标头
#include "framework.h"
#include <afxsock.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>

// 自定义参数
#define INFTY 32767

// 自定义消息
#define WM_LOGIN			WM_USER+100
#define WM_REGISTER			WM_USER+110

//buffer长度定义
#define MAX_BUF 256

// REQUEST服务请求
#define REQUEST_NONE 1000
#define REQUEST_LOGIN 1010
#define REQUEST_REGISTER 1020
#define REQUEST_USERDATA 1030
#define REQUEST_CALCULATE 1040
#define REQUEST_CHARGE 1050
#define REQUEST_VALUE 1060
#define REQUSET_QUIT 1090

// STATUS状态值
#define STATUS_NONE 1000
#define STATUS_TRUE 1011
#define STATUS_FALSE 1010


#endif //PCH_H
