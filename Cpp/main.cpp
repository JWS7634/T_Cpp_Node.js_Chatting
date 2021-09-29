#pragma comment(lib, "ws2_32")
#include <iostream>
#include <thread>
#include <string>
#include <winsock2.h>
#include <windows.h>
#include <CrepeJson.hpp>
#define PORT 8080

using namespace std;

void TF_recv(int* socket){
	char buffer[1024];
	while(1)
	{
		//Memory clear
		memset(&buffer, 0, 1024);
		//When receive data success, print the received data
		if(recv(*socket, buffer, 1024, 0) > 0)
			cout << buffer << endl;
	}
}
   
int main(int argc, char const *argv[])
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 1;

	CrepeJson nsPacket;
	string iBuffer;

    int sock = 0;
    struct sockaddr_in Serv_Addr;
    string buffer = " ";
    sock = socket(AF_INET, SOCK_STREAM, 0);

	//Set Connection Type
    Serv_Addr.sin_family = AF_INET;
    Serv_Addr.sin_port = htons(PORT);
	Serv_Addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	cout << "Name?:";
	getline(cin, iBuffer);

	//made JsonData
	nsPacket.JsonCreate("Name", iBuffer);
	nsPacket.JsonCreate("Data", "");

	//TCP Connection
	cout << "Connection Start" << endl;
    if (connect(sock, (struct sockaddr *)&Serv_Addr, sizeof(Serv_Addr)) < 0)
    {
        cout << "Connection failed" << endl;
        return -1;
    }
	cout << "Connection Success" << endl;

	//While communicate with Server

	//Make receive Thread
	thread TH_recv(TF_recv, &sock);

	//Send loop
	while(1)
	{
		getline(cin, iBuffer);
		if(!iBuffer.compare("quit"))
			break;
		else
		{
			nsPacket.JsonUpdate("Data", iBuffer);
			send(sock, nsPacket.JsonExport(), strlen(nsPacket.JsonExport()), 0);
		}
	}

	//for receive block
	TH_recv.detach();

	//End the Socket
	shutdown(sock,SD_BOTH);
	closesocket(sock);
	WSACleanup();
    return 0;
}