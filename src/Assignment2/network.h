#ifndef _NETWORK_H_
#define _NETWORK_H_

#ifdef _WIN32
#include <WinSock2.h>
#include <Ws2tcpip.h>
#endif

void Socket(int type, int * sock);
int Getaddrinfo(char * _ip, char * _port, addrinfo * addr, int socktype);


#endif