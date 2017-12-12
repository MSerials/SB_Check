#pragma once

#include <stdio.h>
#include <WinSock2.h>
#include <iostream>

class TCPClient
{
public:
	TCPClient();
	~TCPClient();
	TCPClient(CString IP);
	TCPClient(char* ip, char *msg);
	int init(char * seraddress = "127.0.0.1");
	int init(CString serAddress = L"127.0.0.1");
	std::string sendMessage(char * msg);
	std::string sendMessage(CString Msg = L"Error");
	WORD sockVersion;
	WSADATA data;

	SOCKADDR_IN serAddr;
	SOCKET slisten;
	SOCKET sclient;

private:
	int ErrorInfo;
};

