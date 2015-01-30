#ifndef _IP_RESOLUTION_H_
#define _IP_RESOLUTION_H_ 1

#include <WinSock2.h>
#include <Windows.h>
#include <windowsx.h>
#include <string>


#define IP_BUF 128;

std::string ResolveIPFromHost(PCSTR pNodeName);
std::string ResolveHostFromIp(PCSTR pNodeName);

#endif