#include "GarrysMod/Lua/Interface.h"
#include "Message.h"
#include <iostream>
#include <thread>
#include <atomic>

#ifdef _WIN32
	#include <winsock2.h>
	#include <ws2tcpip.h>
	#pragma comment(lib, "ws2_32.lib")
	#define CLOSE_SOCKET closesocket
	#define CLEANUP_WS WSACleanup()
#else
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <unistd.h>
	#define SOCKET int
	#define INVALID_SOCKET -1
	#define SOCKET_ERROR -1
	#define CLOSE_SOCKET close
	#define CLEANUP_WS
#endif

#define PORT 8080
#define HOST "193.31.28.96"

using namespace GarrysMod::Lua;

std::atomic<bool> stopFlag(false);
SOCKET serverSocket = INVALID_SOCKET;
std::thread worker;


void Print(ILuaBase* LUA, std::string msg)
{
	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB); // Push the global table
	LUA->GetField(-1, "print"); // Get the print function
	LUA->PushString(msg.c_str()); // Push our argument
	LUA->Call(1, 0); // Call the function
	LUA->Pop(); // Pop the global table off the stack
}

void WebServerThread(ILuaBase* LUA, SOCKET serverSocket) {
	char buffer[1024] = { 0 };

	while (!stopFlag.load()) {
		int bytesRead = recv(serverSocket, buffer, sizeof(buffer), 0);

		if (bytesRead > 0) {
			std::string data(buffer, bytesRead);
			Print(LUA, "Received: " + data);
			memset(buffer, 0, sizeof(buffer));
		}
		else if (bytesRead == 0) {
			Print(LUA, "Server closed the connection.");
			break;
		}
		else if (stopFlag.load()) {
			Print(LUA, "Stopping thread...");
			break;
		}
		else {
			Print(LUA, "Recv error. Exiting thread.");
			break;
		}
	}

	CLOSE_SOCKET(serverSocket); // Close the socket properly
	Print(LUA, "Thread exited cleanly.");
}

LUA_FUNCTION( MyExampleFunction )
{
	double first_number = LUA->CheckNumber( 1 );
	double second_number = LUA->CheckNumber( 2 );

	LUA->PushNumber( first_number + second_number );
	return 1;
}

LUA_FUNCTION(ConnectToWebServer)
{
	std::string ip = LUA->CheckString(1);

#ifdef _WIN32
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cerr << "WSAStartup failed with error: " << WSAGetLastError() << std::endl;
		return -1;
	}
#endif

	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == INVALID_SOCKET) {
		std::cerr << "Socket creation error." << std::endl;
		CLEANUP_WS;
		return -1;
	}

	sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	if (inet_pton(AF_INET, HOST, &serv_addr.sin_addr) <= 0) {
		std::cerr << "Invalid address / Address not supported" << std::endl;
		CLOSE_SOCKET(serverSocket);
		CLEANUP_WS;
		return -1;
	}

	if (connect(serverSocket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
		std::cerr << "Connection failed." << std::endl;
		CLOSE_SOCKET(serverSocket);
		CLEANUP_WS;
		return -1;
	}

	Print(LUA, "Connected to Node.js backend. Waiting for data...");

	worker = std::thread(WebServerThread, LUA, serverSocket);

	return 0;
}

LUA_FUNCTION(DisconnectWebServer)
{
	// Signal the worker thread to stop
	stopFlag.store(true);

	// Close the socket to unblock `recv`
	CLOSE_SOCKET(serverSocket);

	// Wait for the worker thread to finish
	worker.join();

	std::cout << "Main thread exiting." << std::endl;

#ifdef _WIN32
	CLEANUP_WS;
#endif
}

GMOD_MODULE_OPEN()
{
	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);

	LUA->PushCFunction(MyExampleFunction);
	LUA->SetField(-2, "MyExampleFunction");

	LUA->PushCFunction(ConnectToWebServer);
	LUA->SetField(-2, "ConnectToWebServer");

	LUA->PushCFunction(DisconnectWebServer);
	LUA->SetField(-2, "DisconnectWebServer");

	LUA->Pop();

	return 0;
}


GMOD_MODULE_CLOSE()
{
	return 0;
}