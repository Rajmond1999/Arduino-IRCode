#include <iostream>

#include <stdio.h>
#include "winsock2.h"
#include "ws2tcpip.h"
// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")


void main() {
	WSADATA wsaData;
	SOCKET ClientSocket;
	sockaddr_in ServAddr;
	int Port = 10999, input;
	char SendBuf[4];
	int BufLen = 4;
	int fromlen, len = 4;


	//---------------------------------------------
	// Initialize Winsock
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//---------------------------------------------
	// Create a socket for sending data
	ClientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	//---------------------------------------------
	// Set up the ServAddr structure with the IP address of
	// the receiver (server) (in this example case "192.168.113.85")
	// and the specified port number.
	ServAddr.sin_family = AF_INET;
	ServAddr.sin_port = htons(Port);
	inet_pton(AF_INET, "192.168.0.101", &ServAddr.sin_addr); //inet_pton(AF_INET, "10.0.0.1", &ip4addr.sin_addr);
														 //ws2tcpip.h
	//---------------------------------------------
	// Send a datagram to the receiver

	printf("Sending a datagram to the receiver...\n");
	int sended;
	while (9)
	{
		scanf_s("%i",&input,4);
		memcpy(SendBuf, &input, 4);
		sended=sendto(ClientSocket, SendBuf, len, 0, (SOCKADDR*)&ServAddr, sizeof(ServAddr));
		printf("%i\n", sended);
	}
	//-----------------------------------------------

	// Call the recvfrom function to receive datagrams
	// on the bound socket.

	// kiiratas
	//---------------------------------------------
	// When the application is finished sending, close the socket.
	printf("Finished sending. Closing socket.\n");
	closesocket(ClientSocket);
	//---------------------------------------------
	// Clean up and quit.
	printf("Exiting.\n");
	WSACleanup();
	return;
}