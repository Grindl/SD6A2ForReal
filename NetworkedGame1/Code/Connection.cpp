//#define WIN32_LEAN_AND_MEAN
//#include <windows.h>
//#include <winsock2.h>
//#include <ws2tcpip.h>
//#include <iphlpapi.h>
//#include <stdio.h>
//#include <iostream>
//#include <sstream>
#include <stdlib.h>
//#include <time.h>

#include "Connection.hpp"

Connection::Connection(const char* IPAddress, const char* port)
{
	WSAData myWSAData;
	int WSAResult;
	m_Socket = INVALID_SOCKET;
	struct addrinfo *result = NULL;
	struct addrinfo hints;
	//hostent* HostName =  gethostbyname("smu.gametheorylabs.com");
	//IPAddress = HostName->h_addr_list[0];

	long IPAsLong = inet_addr(IPAddress);
	u_long fionbioFlag = 1;
	//struct sockaddr_in m_SockAddr;

	ZeroMemory( &hints, sizeof(hints) );
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;


	m_SockAddr.sin_family = AF_INET;
	m_SockAddr.sin_port = htons(atoi(port));
	m_SockAddr.sin_addr.S_un.S_addr = IPAsLong;

	WSAResult = WSAStartup(MAKEWORD(2,2), &myWSAData);
	WSAResult = getaddrinfo("smu.gametheorylabs.com", port, &hints, &result);
	m_Socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	WSAResult = ioctlsocket(m_Socket, FIONBIO, &fionbioFlag);
	//WSAResult = connect(m_Socket, result->ai_addr, (int)result->ai_addrlen);
	WSAResult = bind(m_Socket, result->ai_addr, (int)result->ai_addrlen);

	
}

Connection::~Connection()
{
	closesocket(m_Socket);
	WSACleanup();
}

bool Connection::sendPacket(GamePacket pk)
{
	int result = sendto(m_Socket, (char*)&pk, sizeof(pk), 0, (const sockaddr*)&m_SockAddr, sizeof(m_SockAddr));
	bool success = result != -1;
	return success;
}

GamePacket Connection::receivePackets()
{
	struct sockaddr_in recvTarget;
	GamePacket currentData={0,0,0,0, 0.f, 0.f};
	int fromLength = sizeof(recvTarget);
	int errorCode;

	errorCode = recvfrom(m_Socket, (char*)&currentData, sizeof(GamePacket), 0, (sockaddr*)&recvTarget, &fromLength);
	if (currentData.ID != 0)
	{
		int BREAKSUCCESS = 0;
	}
	else
	{
		int newError = WSAGetLastError();
		int BREAKFAIL = 0;
	}
	return currentData;
}