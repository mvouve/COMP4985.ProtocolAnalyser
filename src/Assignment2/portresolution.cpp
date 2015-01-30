#include "portresolution.h"

/*----------------------------------------------------------
-- std::string PortLookup(char * service, char * protocol)
--
-- DATE: January 19 2015
--
-- DESIGNER: MARC VOUVE
--
-- PROGRAMMER: MARC VOUVE
--
-- INTERFACE std::string PortLookup(char * service, char * protocol)
--									char * service: the service to look up
--									char * protocol: the protocol to use, typically TCP or UDP
--
-- RETURNS: Formatted information about the port, including
--			service protocol and port
----------------------------------------------------------*/
std::string PortLookup(char * service, char * protocol)
{
	struct servent *serv;
	std::string retval;
	WSAData wsaData;

	retval = "Service: ";
	retval += service;
	retval += " Protocol: ";
	retval += protocol;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		retval += "Failed to start WSA";
	}

	serv = getservbyname(service, protocol);

	if (serv == NULL)
	{
		retval += "Error getting service by Port";
	}
	else
	{
		retval += " Port: ";
		retval += std::to_string( ntohs(serv->s_port) );
	}
	WSACleanup();
	return retval;
}

/*----------------------------------------------------------
-- std::string ServiceLookup(int pid, char * protocol)
--
-- DATE: January 19 2015
--
-- DESIGNER: MARC VOUVE
--
-- PROGRAMMER: MARC VOUVE
--
-- INTERFACE std::string PortLookup(int pid, char * protocol)
--									int pid: the port of the service
--									char * protocol: the protocol to use, typically TCP or UDP
--
-- RETURNS: Formatted information about the port, including
--			service protocol and port
----------------------------------------------------------*/
std::string ServiceLookup(int pid, char * protocol)
{
	struct servent *serv;
	std::string retval;
	WSAData wsaData;

	retval = "Port: " + std::to_string( pid );
	retval += " Protocol: ";
	retval += protocol;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		retval += "Failed to start WSA";
	}

	serv = getservbyport(htons(pid), protocol);

	if (serv == NULL)
	{
		retval += "Error getting service by Port";
	}
	else
	{
		retval += " Service ";
		retval += serv->s_name;
	}
	WSACleanup();
	return retval;
}