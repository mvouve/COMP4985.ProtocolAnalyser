#ifndef _CONTROL_H_
#define _CONTROL_H_


// ----- HEADERS ------
//#include <Windows.h>
//#include "application.h"
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include "uihelper.h"
#include "network.h"

enum ConnectionError
{
	SUCCESS = 0,
	INVALID_PORT,
	INVALID_HOST,
	FAILED_CONNECT
};

ConnectionError ControlConnect(char * _ip, char * _port, HWND _wnd, UINT msg, int * sock);
ConnectionError ControlListen(char * _port, HWND _wnd, UINT msg, int * sock);

#endif