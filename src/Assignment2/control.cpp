#include "control.h"
ConnectionError ControlConnect(char * _ip, char * _port, HWND _wnd, UINT msg, int * sock )
{
	addrinfo * server = (addrinfo*)malloc(sizeof(addrinfo));

	memset(server, 0, sizeof(addrinfo));

	// Open TCP socket
	//Socket(SOCK_STREAM, sock);

	// resolve the host name
	if (Getaddrinfo(_ip, _port, server, SOCK_STREAM))
	{
		return INVALID_HOST;
	}

	*sock = socket(server->ai_family, server->ai_socktype, server->ai_protocol);
	bind(*sock, server->ai_addr, sizeof server);

	// attempt to connect to the server.
	if (connect(*sock, server->ai_addr, sizeof(server->ai_addr)))
	{
		return FAILED_CONNECT;
	}

	
	
	WSAAsyncSelect(*sock, _wnd, msg, FD_ALL_EVENTS);

	free(server);
}



ConnectionError ControlListen(char * _port, HWND _wnd, UINT msg, int * sock)
{
	addrinfo * client = (addrinfo*) malloc(sizeof(addrinfo));

	// Open TCP socket
	Socket(SOCK_STREAM, sock);

	if (!(Getaddrinfo(NULL, _port, client, SOCK_STREAM)))
	{
		return FAILED_CONNECT;
	}

	// Listen for all events on control port
	WSAAsyncSelect(*sock, _wnd, msg, FD_ALL_EVENTS);

	free(client);
}