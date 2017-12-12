#include "stdafx.h"
#include "TCPServer.h"

//init
TCPServer::TCPServer()
{
	
}


TCPServer::~TCPServer()
{

}

//实际上是UDP不安全协议
void TCPServer::Monitoring()
{

#if 1
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return ;
	}

	//创建套接字  
	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (slisten == INVALID_SOCKET)
	{
		printf("socket error !");
		return ;
	}

	//绑定IP和端口  
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8889);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf("bind error !");
		return;
	}

	//开始监听  
	if (listen(slisten, 5) == SOCKET_ERROR)
	{
		printf("listen error !");
		return ;
	}

	//循环接收数据  
	SOCKET sClient;
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	while (1){
	char revData[4096] = { 0 };
	sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
	if (sClient == INVALID_SOCKET)
	{
		printf("accept error !");
		continue;
	}
	while (true)
	{

#ifdef _TEST
		printf("接受到一个连接：%s \r\n", inet_ntoa(remoteAddr.sin_addr));
#endif
		static DWORD tick = GetTickCount();
		//接收数据  
		int ret = recv(sClient, revData, 255, 0);
		int flag = 0;
		if (ret > 0 && ret <4095)
		{
			revData[ret] = 0x00;
			flag = 1; tick = GetTickCount();
#ifdef _TEST
			printf("%s\n",revData);
#endif
		}
		if ((GetTickCount() - tick)> 3000) { closesocket(sClient); break; }
		//发送数据 
	
			if (flag)
			{
				CString command(revData);
				{
					int sel = 0;
					if (0 == command.Compare(L"get"))
					{
						char * sendData = (char*)(LPCSTR)(CStringA)g.msg_socket;
						send(sClient, sendData, strlen(sendData), 0);// , (sockaddr *)&remoteAddr, nAddrLen);
					}
					else if (0 == command.Compare(L"query"))
					{
						char * sendData = (char*)(LPCSTR)(CStringA)g.CurrentPrjName;
						send(sClient, sendData, strlen(sendData), 0);// , (sockaddr *)&remoteAddr, nAddrLen);
					}
					else
					{
						g.CurrentPrjName = command;
						if (NULL != g.MainCtrl)
							::SendMessage(g.MainCtrl, WMMSG_SOCKET_COMMAND, 0, SELECTPRJBYNAME);
						char * sendData = "切换项目中\n";
						send(sClient, sendData, strlen(sendData), 0);
					}
				}
			}
			else
			{
				char * sendData = "数据接收不正确！\n";
			}
		
	//	closesocket(sClient);
	}
	}
	closesocket(slisten);
	WSACleanup();
	return ;

#else
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 2);
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return;
	}

	SOCKET serSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (serSocket == INVALID_SOCKET)
	{
		printf("socket error !");
		return;
	}

	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(8889);
	serAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(serSocket, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
	{
		printf("bind error !");
		closesocket(serSocket);
		return;
	}

	sockaddr_in remoteAddr;
	remoteAddr.sin_family = AF_INET;
	remoteAddr.sin_port = htons(8800);
	remoteAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	int nAddrLen = sizeof(remoteAddr);
	while (true)
	{
		char recvData[255];
		int ret = recvfrom(serSocket, recvData, 255, 0, (sockaddr *)&remoteAddr, &nAddrLen);
		if (ret > 0)
		{
			recvData[ret] = 0x00;
			CString command(recvData);
			{
				int sel = 0;
				if (0 == command.Compare(L"get"))
				{			
					char * sendData = (char*)(LPCSTR)(CStringA)g.msg_socket;
					sendto(serSocket, sendData, strlen(sendData), 0, (sockaddr *)&remoteAddr, nAddrLen);
					printf("start to send\n");
				}
				else if (0 == command.Compare(L"query"))
				{
					char * sendData = (char*)(LPCSTR)(CStringA)g.CurrentPrjName;
					sendto(serSocket, sendData, strlen(sendData), 0, (sockaddr *)&remoteAddr, nAddrLen);
				}
				else
				{
					g.CurrentPrjName = command;
					if (NULL != g.MainCtrl)
						::SendMessage(g.MainCtrl, WMMSG_SOCKET_COMMAND, 0, SELECTPRJBYNAME);
				}
			}
			int data1 = remoteAddr.sin_addr.S_un.S_addr >> 12;
			int data2 = (remoteAddr.sin_addr.S_un.S_addr & 0xFF0000) >> 8;
			int data3 = (remoteAddr.sin_addr.S_un.S_addr & 0xFF00) >> 4;
			int data4 = 0;
			char * sendData = "already recieved message\n";
			sendto(serSocket, sendData, strlen(sendData), 0, (sockaddr *)&remoteAddr, nAddrLen);
		}
		else
		{		
			char * sendData = "error_in_data\n";
			sendto(serSocket, sendData, strlen(sendData), 0, (sockaddr *)&remoteAddr, nAddrLen); 
		}
	//end:
	//	printf("recieve something\n");
	}
	closesocket(serSocket);
	WSACleanup();

#endif
}