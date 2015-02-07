#ifndef _CONTROL_H_
#define _CONTROL_H_


// ----- HEADERS ------
//#include <Windows.h>
//#include "application.h"
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include "uihelper.h"

ConnectionError ControlConnect(LPCSTR ipAddr,LPCSTR port);

enum ConnectionError
{
	INVALID_PORT,
	INVALID_HOST
};

//

#endif