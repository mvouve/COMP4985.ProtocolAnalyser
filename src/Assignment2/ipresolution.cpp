#include "ipresolution.h"
#include <string>

/*----------------------------------------------------------
-- std::string ResolveIPFromHost(PCSTR pNodeName)
--
-- DATE: January 19 2015
--
-- DESIGNER: MARC VOUVE
--
-- PROGRAMMER: MARC VOUVE
--
-- INTERFACE std::string ResolveIPFromHost(PCSTR pNodeName)
--									PCSTR pNodeName the Host name to look up
--
-- RETURNS: Formatted information including hostname ip and aliases
----------------------------------------------------------*/
std::string ResolveIPFromHost(PCSTR pNodeName)
{
	WSADATA wsaData;
	std::string retval = "";
	hostent * hp;
	

	// init IP services for windows
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{
		return "Failed to start WSA";
	}

	// gets host by name and stores it in result, returns function with
	// an error if an error is detected.
	hp = gethostbyname(pNodeName);
	if (hp == NULL)
	{
		switch (WSAGetLastError())
		{
		case HOST_NOT_FOUND:
			retval += pNodeName;
			retval += ": Host not Found\r\n";
			break;
		case TRY_AGAIN:
			retval += pNodeName;
			retval += ": Try again Later\r\n";
			break;
		case NO_RECOVERY:
			retval += pNodeName;
			retval += ": No Recovery\r\n";
			break;
		case NO_ADDRESS:
			retval += pNodeName;
			retval += ": No IP Address\r\n";
			break;
		default:
			retval += pNodeName;
			retval += ": Unknown Issue\r\n";
		}
		
	}
	else
	{

		for (char ** p = hp->h_addr_list; *p != 0; p++)
		{
			struct in_addr in;

			memcpy(&in.s_addr, *p, sizeof(in.s_addr));
			retval += "\r\n IP Address: ";
			retval += inet_ntoa(in);
			retval += "\r\n Host Name: ";
			retval += hp->h_name;
			retval += "\r\n\t\t Aliases: \r\n";
			for (char ** q = hp->h_aliases; *q != 0; q++)
			{
				retval += "\t\t ";
				retval += *q;
				retval += "\r\n";
			}
		}

		retval += "\r\n";
	}
	WSACleanup();

	return retval;
}

/*----------------------------------------------------------
-- std::string ResolveHostFromIp(PCSTR pNodeName)
--
-- DATE: January 19 2015
--
-- DESIGNER: MARC VOUVE
--
-- PROGRAMMER: MARC VOUVE
--
-- INTERFACE std::string ResolveHostFromIp(PCSTR pNodeName)
--									PCSTR pNodeName the IP address of the host
--
-- RETURNS: Formatted information including hostname ip and aliases
----------------------------------------------------------*/
std::string ResolveHostFromIp(PCSTR pNodeName)
{
	char ip_address[128];
	int addr;
	char **p;
	struct in_addr my_addr;

	std::string retval;
	WSADATA wsaData;
	hostent * hp;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return "Failed to start WSA\r\n";
	}
	else
	{
		if ((addr = inet_addr(pNodeName)) == 0)
		{
			retval = "Names must be in dotted decimal notation: X.X.X.X\r\n";
		}
		strcpy_s(ip_address, pNodeName);
		my_addr.s_addr = inet_addr(ip_address);
		hp = gethostbyaddr( (char *)&my_addr, PF_INET, sizeof(my_addr));

		if (hp == NULL)
		{
			retval = "Failed to find Host info for IP: ";
			retval =+ pNodeName;
		}
		else
		{
			for (char ** p = hp->h_addr_list; *p != 0; p++)
			{
				struct in_addr in;

				memcpy(&in.s_addr, *p, sizeof(in.s_addr));
				retval += "\r\n IP Address: ";
				retval += inet_ntoa(in);
				retval += "\r\n Host Name: ";
				retval += hp->h_name;
				retval += "\r\n\t\t Aliases: \r\n";
				for (char ** q = hp->h_aliases; *q != 0; q++)
				{
					retval += "\t\t ";
					retval += *q;
					retval += "\r\n";
				}
			}
		}
	}
	WSACleanup();

	return retval + "\r\n";
}