#include "control.h"
ConnectionError ClientConnect(LPCSTR _ipAddr, LPCSTR _port)
{
	INT port;
	PADDRINFOA server;
	SOCKET sock;

	

	if (!(port = atoi(_port)))
	{
		return INVALID_PORT;
	}

	sock = htons(port);
	
	// resolve the host name
	if (!(GetAddrInfoA(_ipAddr, NULL, NULL, &server)))
	{
		return INVALID_HOST;
	}

//	TCPConnect();
}

INT WINAPI ControlPortThread()
{

}