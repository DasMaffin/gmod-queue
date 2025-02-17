#include "GarrysMod/Lua/Interface.h"
#include "Message.h"
#include "tools.h"
//#include <iostream>
#include <thread>
#include <atomic>
#include <json/json.h>

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

void processData(ILuaBase* LUA, const std::string& data) {
	Print(LUA, "Data received: " + data);
	// Perform your task here
	Json::Value jsonData;
	Json::CharReaderBuilder readerBuilder;
	std::string errs;

	std::istringstream sstream(data);
	if (Json::parseFromStream(readerBuilder, sstream, &jsonData, &errs)) {
		std::string msg = jsonData["message"].asString();
		std::string timestamp = jsonData["timestamp"].asString();

		// Create a Message instance and print it
		Message msgObj(msg, timestamp, LUA);
		msgObj.print();
	}
	else {
		Error(LUA, "Failed to parse JSON: " + errs);
	}
}

void WebServerThread(ILuaBase* LUA) {
	char buffer[1024] = { 0 };

	while (!stopFlag.load()) {
		int bytesRead = recv(serverSocket, buffer, sizeof(buffer), 0);

		if (bytesRead > 0) {
			std::string data(buffer, bytesRead);
			processData(LUA, data);
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


LUA_FUNCTION(SendToWebServer)
{
	std::string data = LUA->CheckString(1);

	if (serverSocket == INVALID_SOCKET) {
		Error(LUA, "Socket is not connected.");
		return 0;
	}

	int result = send(serverSocket, data.c_str(), data.size(), 0);
	if (result == SOCKET_ERROR) {
		Error(LUA, "Failed to send data.");
		return 0;
	}

	Print(LUA, "Data sent successfully.");
	return 0;
}

LUA_FUNCTION(ConnectToWebServer)
{
	std::string ip = LUA->CheckString(1);

#ifdef _WIN32
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		Error(LUA, "WSAStartup failed with error: " + WSAGetLastError());
		return -1;
	}
#endif

	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == INVALID_SOCKET) {
		Error(LUA, "Socket creation error.");
		CLEANUP_WS;
		return -1;
	}

	sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	if (inet_pton(AF_INET, HOST, &serv_addr.sin_addr) <= 0) {
		Error(LUA, "Invalid address / Address not supported");
		CLOSE_SOCKET(serverSocket);
		CLEANUP_WS;
		return -1;
	}

	if (connect(serverSocket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
		Error(LUA, "Connection failed.");
		CLOSE_SOCKET(serverSocket);
		CLEANUP_WS;
		return -1;
	}

	Print(LUA, "Connected to Node.js backend. Waiting for data...");

	worker = std::thread(WebServerThread, LUA);

	return 0;
}

LUA_FUNCTION(DisconnectWebServer)
{
	stopFlag.store(true);

	CLOSE_SOCKET(serverSocket);

	worker.join();

	Print(LUA, "Main thread exiting.");

#ifdef _WIN32
	CLEANUP_WS;
#endif
	return 0;
}

GMOD_MODULE_OPEN()
{
	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);

	LUA->PushCFunction(SendToWebServer);
	LUA->SetField(-2, "SendToWebServer");

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