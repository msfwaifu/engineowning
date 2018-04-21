#include "EO_Main.h"

#include <iostream>
#pragma comment(lib,"ws2_32.lib")

std::string ServerBuffer;

int GetString()
{
	WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        MSG( "WSAStartup failed.\n");
        system("pause");
        return 1;
    }
    SOCKET Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    struct hostent *host;
	host = gethostbyname("84.200.24.182");
    SOCKADDR_IN SockAddr;
    SockAddr.sin_port=htons(80);
    SockAddr.sin_family=AF_INET;
    SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);
    if(connect(Socket,(SOCKADDR*)(&SockAddr),sizeof(SockAddr)) != 0){
        MSG("could not connect");
        
        return 1;
    }
    char szAuthRequest[1024];
	char* Username = (char*)0x0672796A;
	sprintf(szAuthRequest, "GET /tracker/tracker.php?user=%s \r\nHost: www.engineowning.eu\r\nContent-Type: text/html\r\n\r\n",Username);
	send(Socket, szAuthRequest, strlen(szAuthRequest), 0);
	
	
    int nDataLength;

	char buffer[10000];
	ZeroMemory(buffer,10000);

    while ((nDataLength = recv(Socket,buffer,10000,0)) > 0){        
        int i = 0;
		ServerBuffer = "";
        while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r') {
			ServerBuffer += buffer[i];
            i += 1;

        }
    }

    closesocket(Socket);
	WSACleanup();
    return 0;
}

void TrackerThread()
{
	while(true)
	{
		GetString();
		Sleep(5000);
	}

}