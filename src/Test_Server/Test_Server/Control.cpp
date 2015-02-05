#include "Server.h"

DWORD WINAPI udpListeningThread()
{
	UDPStartListen();
}