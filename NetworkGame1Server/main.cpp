#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <vector>

#pragma comment(lib, "Ws2_32.lib")



struct GamePacket
{
	char ID;
	char r, g, b;
	float x;
	float y;
};

struct Client
{
	struct sockaddr_in m_sockAddr;
	float m_timeOfLastReport;
};

struct sockaddr_in g_serverSockAddr;
SOCKET m_Socket;
std::vector<Client> g_clients;

void startServer(const char* IPAddress, const char* port)
{
	WSAData myWSAData;
	int WSAResult;
	m_Socket = INVALID_SOCKET;
	//hostent* HostName =  gethostbyname("smu.gametheorylabs.com");
	//IPAddress = HostName->h_addr_list[0];

	long IPAsLong = inet_addr(IPAddress);
	u_long fionbioFlag = 1;

	g_serverSockAddr.sin_family = AF_INET;
	g_serverSockAddr.sin_port = htons(atoi(port));
	g_serverSockAddr.sin_addr.s_addr = INADDR_ANY;

	WSAResult = WSAStartup(MAKEWORD(2,2), &myWSAData);
	m_Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	WSAResult = ioctlsocket(m_Socket, FIONBIO, &fionbioFlag);
	WSAResult = bind(m_Socket, (struct sockaddr*)&g_serverSockAddr, sizeof(g_serverSockAddr));
}

GamePacket receive()
{
	int WSAResult;
	GamePacket pk = {0,0,0,0, 0.f, 0.f};
	Client tempClient;
	int recvSize = sizeof(tempClient.m_sockAddr);
	bool newClient = true;

	WSAResult = recvfrom(m_Socket, (char*)&pk, sizeof(pk), 0,  (sockaddr*)&(tempClient.m_sockAddr), &recvSize);
	//tempClient.m_sockAddr.sin_addr.s_addr = htonl(tempClient.m_sockAddr.sin_addr.s_addr);
	if (WSAResult != -1)
	{
		for (unsigned int ii = 0; ii < g_clients.size(); ii++)
		{
			if (tempClient.m_sockAddr.sin_addr.S_un.S_addr == g_clients[ii].m_sockAddr.sin_addr.S_un.S_addr)
			{
				newClient = false;
				//TODO update the time
			}
		}
		if (newClient)
		{
			//TODO give a time
			g_clients.push_back(tempClient);
		}
	}
	else
	{
		WSAResult = WSAGetLastError();
		int BREAKNOW = 0;
	}

	return pk;
}

void sendToAllClients(GamePacket pk)
{
	int WSAResult;
	for (unsigned int ii = 0; ii < g_clients.size(); ii++)
	{
		WSAResult = sendto(m_Socket, (char*)&pk, sizeof(pk), 0, (const sockaddr*)&(g_clients[ii].m_sockAddr), sizeof(g_clients[ii].m_sockAddr));
	}
}

int main()
{
	startServer("127.0.0.1", "8080");
	while(true)
	{
		GamePacket temp = receive();
		if (temp.ID !=0)
		{
			sendToAllClients(temp);
		}
		//TODO remove dead clients
		Sleep(1);
	}

	return 0;
}