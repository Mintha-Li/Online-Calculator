// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

#define IPADDRESS L"127.0.0.1"
#define PORT 8080

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

// 运算定义
#define PLUS 0
#define MINUS 1
#define MULTIPLY 2
#define DIVIDE 3

// 添加要在此处预编译的标头
#include "framework.h"
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>

#endif //PCH_H

