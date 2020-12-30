#include <iostream>

#include <stdio.h>
#include "winsock2.h"
#include "ws2tcpip.h"
// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")


void main(){
	WSADATA wsaData;
	SOCKET ListenSocket;
	sockaddr_in ServAddr;
	sockaddr_in RecvAddr;
	int Port = 13 , Port2=10999;
	char SendBuf[1024];
	char FAR RecBuf[1024];
	int BufLen = 1024;
	int fromlen, len;
	SYSTEMTIME st, lt;

	//---------------------------------------------
	// Initialize Winsock
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//---------------------------------------------
	// Create a socket for sending data

	ListenSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	//---------------------------------------------

	ServAddr.sin_family = AF_INET;
	ServAddr.sin_port = htons(Port2);
	inet_pton(AF_INET, "127.0.0.1", &ServAddr.sin_addr);
	

	if (bind(ListenSocket,
		(SOCKADDR*)&ServAddr,
		sizeof(ServAddr)) == SOCKET_ERROR) {
		printf("bind() failed.\n");
		closesocket(ListenSocket);
		return;
	}




	//---------------------------------------------

	printf("Receiving datagrams...\n");
	fromlen = sizeof(RecvAddr);
	int i = recvfrom(ListenSocket, RecBuf, BufLen, 0, (SOCKADDR*)&RecvAddr, &fromlen);
	printf("%i\n", i);
	if (i < 0) {
		int f = WSAGetLastError();
		f = f;
	}


	//-----------------------------------------------
	
	SendBuf[0] = 'a';
	SendBuf[1] = 'l';
	SendBuf[2] = 'm';
	SendBuf[3] = 'a';
	SendBuf[4] = '\0';
	GetLocalTime(&lt);

	len = strlen(SendBuf)+1;

	printf("Sending a datagram to the receiver...\n");
	printf("%i\n", sendto(ListenSocket, SendBuf, len, 0, (SOCKADDR*)&RecvAddr, sizeof(RecvAddr)));


	printf("Finished sending. Closing socket.\n");
	closesocket(ListenSocket);
	//---------------------------------------------
	// Clean up and quit.
	printf("Exiting.\n");
	WSACleanup();
	return;
}