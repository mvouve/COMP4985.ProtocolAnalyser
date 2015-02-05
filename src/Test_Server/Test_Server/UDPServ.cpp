#include "UDPServ.h"

VOID UDPStartListen()
{
	SOCKET sd;
	struct sockaddr_in server, client;
	int client_len;
	char buffer[MAX_LEN];
	int bytesRead;

#ifdef _WIN32	// if win32 is defined.
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

		if (sd = (socket(PF_INET, SOCK_DGRAM, 0)) < 0)
		{
			perror("can not open socket");
		}

		memset((char*)&server, 0, sizeof(server));
		server.sin_family = AF_INET;
		server.sin_port = htons(UDP_PORT);
		server.sin_addr.s_addr = htonl(INADDR_ANY);

		if (bind(sd, (struct sockaddr *) &server, sizeof(server)) < 0)
		{
			perror("failed to bind socket");
		}

		for (;;)	// <3 Eric
		{
			client_len = sizeof(client);
			if (bytesRead = recvfrom(sd, buffer, MAX_LEN, 0, (struct sockaddr *)&client, &client_len) < 0)
			{
				MessageBox(NULL, "Error: could not read UDP", "Error", MB_OK);
				OutputDebugString(buffer);
			}
		}
		
}