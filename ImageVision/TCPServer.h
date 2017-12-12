#pragma once

#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib,"ws2_32.lib")

class TCPServer
{
public:
	TCPServer();
	~TCPServer();
	void Monitoring();
};

