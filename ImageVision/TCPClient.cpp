#include "stdafx.h"
#include "TCPClient.h"
#pragma  comment(lib,"ws2_32.lib")


TCPClient::TCPClient()
{
	ErrorInfo = 0;
}


TCPClient::~TCPClient()
{
	closesocket(sclient);
	WSACleanup();
}


TCPClient::TCPClient(char* ip,char *msg)
{
//加载套接字
WSADATA wsaData;
char buff[1024];
memset(buff, 0, sizeof(buff));

if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
{
	printf("Failed to load Winsock");
	return;
}

SOCKADDR_IN addrSrv;
addrSrv.sin_family = AF_INET;
addrSrv.sin_port = htons(5099);
addrSrv.sin_addr.S_un.S_addr = inet_addr(ip);

//创建套接字
SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);
if (SOCKET_ERROR == sockClient) {
	printf("Socket() error:%d", WSAGetLastError());
	return;
}

//向服务器发出连接请求
if (connect(sockClient, (struct  sockaddr*)&addrSrv, sizeof(addrSrv)) == INVALID_SOCKET) {
	printf("Connect failed:%d", WSAGetLastError());
	return;
}
else
{
	//接收数据
	recv(sockClient, buff, sizeof(buff), 0);
	printf("%s\n", buff);
}

//发送数据
const char buff1[] = "hello, this is a Client....";
send(sockClient, msg, strlen(msg), 0);

//关闭套接字
closesocket(sockClient);
WSACleanup();
}







TCPClient::TCPClient(CString IP)
{
	ErrorInfo = 0;
	char * seraddress = (char*)(LPCSTR)(CStringA)IP;
	if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
	{
		ErrorInfo = 1;
	}

	//sclient = socket(AF_INET, SOCK_STREAM, 0);
	sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sclient == SOCKET_ERROR)
		//if (sclient == INVALID_SOCKET)
	{
		ErrorInfo = 2;
	}

	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(5099);
	serAddr.sin_addr.S_un.S_addr = inet_addr(seraddress);
	if (connect(sclient, (struct sockaddr *)&serAddr, sizeof(serAddr)) == INVALID_SOCKET)
	{
		closesocket(sclient);
		ErrorInfo = 3;
	}
}

int TCPClient::init(CString serAddress)
{
//	sockVersion = ;
	char * seraddress = (char*)(LPCSTR)(CStringA)serAddress;
	if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
	{
		return 1;
	}

	sclient = socket(AF_INET, SOCK_STREAM, 0);
	// = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sclient == SOCKET_ERROR)
	//if (sclient == INVALID_SOCKET)
	{
		printf("invalid socket !");
		return 2;
	}

	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(8888);
	serAddr.sin_addr.S_un.S_addr = inet_addr(seraddress);
	if (connect(sclient, (struct sockaddr *)&serAddr, sizeof(serAddr)) == INVALID_SOCKET)
	{
		closesocket(sclient);
		return 3;
	}
	return 0;
}


int TCPClient::init(char * seraddress)
{
	if (WSAStartup(sockVersion, &data) != 0)
	{
		return 1;
	}


	sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sclient == INVALID_SOCKET)
	{
		printf("invalid socket !");
		return 2;
	}

	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(8888);
	serAddr.sin_addr.S_un.S_addr = inet_addr(seraddress);
	if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
	{
		printf("connect error !");
		closesocket(sclient);
		return 3;
	}


	return 0;
}

//发送的数据格式会在app那个类里看见
//格式为  "SawBar_Check,[n],TOTAL,[_totla],OK,[_okTotal],NG,[_NGTotal],[OKORNG]\n" 
//其中SawBar_Check标识了这台机器的名称，n是这台机器的ID号,
 std::string TCPClient::sendMessage(char * msg)
{
	send(sclient, msg, strlen(msg), 0);
	char recData[255]= "info_error";
	int ret = recv(sclient, recData, 255, 0);
	if (ret > 0)
	{
		recData[ret] = 0x00;
	}
	std::string str = recData;
	closesocket(sclient);
	WSACleanup();
	return str;
}



 std::string TCPClient::sendMessage(CString Msg)
 {
	 if (ErrorInfo) return std::string("e");
	 char * msg = (char*)(LPCSTR)(CStringA)Msg;
	 send(sclient, msg, strlen(msg), 0);
	 char recData[255] = { 0x0 };
	 int ret = recv(sclient, recData, 255, 0);
	 if (ret > 0)
	 {
		 recData[ret] = 0x00;
	 }
	 closesocket(sclient);
	 WSACleanup();
	 return std::string("ok");
 }
