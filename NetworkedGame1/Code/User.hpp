#pragma once
#ifndef include_USER
#define include_USER

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
//#include <stdio.h>
//#include <iostream>
//#include <sstream>
//#include <stdlib.h>
//#include <time.h>
#include "Entity.hpp"

struct GamePacket
{
	char ID;
	char r, g, b;
	float x;
	float y;
};

enum USER_TYPE{USER_LOCAL, USER_REMOTE};

class User
{
public:
	User();

	Entity m_unit;
	USER_TYPE m_userType;

	GamePacket sendInput();
	void update(float deltaSeconds);
	void render();
};

#endif