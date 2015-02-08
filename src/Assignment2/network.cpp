/*---------------------------------------------------------------------------------------
--	SOURCE FILE:		network.cpp - A simple TCP client program.
--
--	PROGRAM:			protocol_analyser.exe
--
--	FUNCTIONS:			Socket(int type, int * sock);
--
--	DATE:				January 22, 2015
--
--	REVISIONS:			(Date and Description)
--
--	DESIGNERS:			Marc Vouve
--
--	PROGRAMMERS:		Marc Vouve
--
--	NOTES:
--  This file contains Network wrapper functions that are intended to be easily portable
--  between operating systems that use berkly prototypes.
---------------------------------------------------------------------------------------*/

#include "network.h"

/* -------------------------------------------------------------------------------------
-- FUNCTION: Socket
--
-- DATE: January 22, 2015
--
-- DESIGNERS: Marc Vouve
--
-- PROGRAMMERS: Marc Vouve
--
-- INTERFACE: void Socket( int type, int * sock )
--							int type: one of either SOCK_DGRAM for UDP or
--									                SOCK_STREAM for TCP
--							int * sock: a pointer to the location in which to save the
--										socket.
--
-- NOTES:
-- This function creates a socket based off the UDP or TCP types.
--------------------------------------------------------------------------------------*/
void Socket( int type, int * sock )
{
	switch (type)
	{
	case SOCK_STREAM:
		*sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		break;
	case SOCK_DGRAM:	// AF_UNSPEC works with IPv4 and IPv6. Hopefully windows likes.
		*sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		break;
	default:
		*sock = 0;
	}
	
}




/* -------------------------------------------------------------------------------------
-- FUNCTION: Getaddrinfo
--
-- DATE: January 22, 2015
--
-- DESIGNERS: Marc Vouve
--
-- PROGRAMMERS: Marc Vouve
--
-- INTERFACE: int Getaddrinfo(char * _ip, char * _port, addrinfo * addr, int socktype )
--								char _ip: The ip or hostname to connect to.
--								char _port: The service or port to connect to.
--								addrinfo * addr: the addr to struct to add the connection
--												 info to.
--
-- RETURNS: int 0 on success, 1 on failure.
--
-- NOTES:
-- This function creates a socket based off the UDP or TCP types.
--------------------------------------------------------------------------------------*/
int Getaddrinfo(char * _ip, char * _port, addrinfo * addr, int socktype )
{
	addrinfo hints;
	addrinfo * temp;

	temp = (addrinfo *)malloc(sizeof temp);
	memset(&hints, 0, sizeof hints);
	memset(&temp, 0, sizeof temp);

	hints.ai_family = AF_INET;
	hints.ai_socktype = socktype;
	
	if (getaddrinfo(_ip, _port, &hints, &temp ))
	{
		return 1;
	}

	memcpy(addr, temp, sizeof(addrinfo));
	

	return 0;
}
