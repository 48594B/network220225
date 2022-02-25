#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>
#include <string>


using namespace std;

#pragma comment(lib, "ws2_32.lib")

struct  NumberPacket{
	int Number1;
	int Number2;
};

int main()
{
	WSAData WsaData;
	
	if (WSAStartup(MAKEWORD(2, 2), &WsaData))
	{
		cout << "Winsock Error : " << GetLastError() << endl;
		exit(-1);
	}


	SOCKET ServerSocket;
	ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (ServerSocket == INVALID_SOCKET)
	{
		cout << "Socket Error : " << GetLastError() << endl;
		exit(-1);
	}

	SOCKADDR_IN ServerAddr;
	memset(&ServerAddr, 0, sizeof(ServerAddr));
	ServerAddr.sin_port = htons(50000);
	ServerAddr.sin_family = PF_INET;
	ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(ServerSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)
	{
		cout << "Connet Error : " << GetLastError() << endl;
		exit(-1);
	}

	string Numbers = "30\n";
	send(ServerSocket, Numbers.c_str(), Numbers.length() + 1, 0);
	Numbers = "20\n";
	send(ServerSocket, Numbers.c_str(), Numbers.length() + 1, 0);

	char Result[1024];
	recv(ServerSocket, Result, 1023, 0);

	cout << "Server Sended : " << Result << endl;

	closesocket(ServerSocket);

	WSACleanup();

	return 0;
}
