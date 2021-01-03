#include <iostream>

#include <stdio.h>
#include "winsock2.h"
#include "ws2tcpip.h"
#pragma comment(lib, "Ws2_32.lib")


int main()
{
	WSADATA wsaData;
	SOCKET ListenSocket;
	sockaddr_in ServAddr;
	sockaddr_in RecvAddrCommander;
	int Port = 10999;
	char SendBuf[4];
	char FAR RecBuf[4];
	int BufLen = 4;
	int fromlen, CommandLen = -1, NumberOfClients = 1;
	SYSTEMTIME st, lt;

	// Initialize Winsock
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	// Create a socket for sending data

	ListenSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	ServAddr.sin_family = AF_INET;
	ServAddr.sin_port = htons(Port);
	//ServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	inet_pton(AF_INET, "127.0.0.1", &ServAddr.sin_addr);

	if (bind(ListenSocket,
		(SOCKADDR*)&ServAddr,
		sizeof(ServAddr)) == SOCKET_ERROR) {
		printf("bind() failed.\n");
		closesocket(ListenSocket);
		return 0;
	}

	//------------------------
	//initializing clients

	sockaddr_in RecvAddr[1024];
	for (int i = 0; i < NumberOfClients; ++i)
	{
		while (CommandLen < 0) {
			fromlen = sizeof(RecvAddr[i]);
			CommandLen = recvfrom(ListenSocket, RecBuf, BufLen, 0, (SOCKADDR*)&(RecvAddr[i]), &fromlen);
			printf("%i %c", CommandLen, (char)(*RecBuf));
		}
	}

	printf("Receiving datagrams...\n");

	int code;

	while (9)
	{
		while (CommandLen < 0)
		{
			CommandLen = recvfrom(ListenSocket, RecBuf, BufLen, 0, (SOCKADDR*)&RecvAddrCommander, &fromlen);
		}
		memcpy(&code, RecBuf, 4);
		printf("%i %i\n", code, CommandLen);

		for (int i = 0; i < NumberOfClients; ++i)
		{
			CommandLen = sendto(ListenSocket, SendBuf, CommandLen, 0, (SOCKADDR*)&(RecvAddr[i]), sizeof(RecvAddr[i]));
			printf("%i %i\n", code, CommandLen);
		}
		CommandLen = -1;
	}


	//---------------------------------------------
	// Clean up and quit.
	closesocket(ListenSocket);
	printf("Exiting.\n");
	WSACleanup();
	return 0;
}

