#include "GameServer.h"
#include "tools.h"
#include <thread>
#include <string>

GameServer::GameServer(const std::string& serverIP, int serverPort, const std::string& webServerIP, int webServerPort, int maxPlayers, GarrysMod::Lua::ILuaBase* lua)
    : serverIP(serverIP), serverPort(serverPort), webServerIP(webServerIP), webServerPort(webServerPort), serverSocket(INVALID_SOCKET), webSocket(INVALID_SOCKET), connected(false), maxPlayers(maxPlayers), LUA(lua)
{
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        Error(LUA, "Winsock initialization failed.");
        return;
    }
#endif
}

GameServer::~GameServer()
{
    cleanup();
}

bool GameServer::connectToWebServer()
{
    // Create the socket for connection
    webSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (webSocket == INVALID_SOCKET)
    {
        Error(LUA, "Socket creation failed.");
        return false;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(webServerPort);
    inet_pton(AF_INET, webServerIP.c_str(), &serverAddr.sin_addr);

    // Connect to the webserver
    if (connect(webSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        Error(LUA, "Failed to connect to the webserver.");
        return false;
    }

    connected.store(true);

    std::thread listenerThread(&GameServer::listenForData, this);
    listenerThread.detach();

    sendInitPackage();

    return true;
}

void GameServer::sendInitPackage()
{
    if (!connected.load())
    {
        Error(LUA, "Not connected to web server.");
        return;
    }

    std::string initData = "{  \"action\": \"initServer\", \"serverIP\": \"" + serverIP + "\", \"maxPlayers\": " + std::to_string(maxPlayers) + ", \"isQueueServer\": false }";
    int bytesSent = send(webSocket, initData.c_str(), initData.size(), 0);
    if (bytesSent == SOCKET_ERROR)
    {
        Error(LUA, "Failed to send new player data to web server.");
        return;
    }
    Print(LUA, "Sent initialization data: " + initData);
}

void GameServer::sendNewPlayer(const std::string& playerName)
{
    if (!connected.load())
    {
        Error(LUA, "Not connected to web server. Cannot send new player.");
        return;
    }

    std::string playerData = "{ \"action\": \"addPlayer\", \"playerName\": \"" + playerName + "\", \"serverIP\": \"" + serverIP + "\" }";

    int bytesSent = send(webSocket, playerData.c_str(), playerData.size(), 0);
    if (bytesSent == SOCKET_ERROR)
    {
        Error(LUA, "Failed to send new player data to web server.");
        return;
    }
    Print(LUA, "Sent new player to backend: " + playerData);
}


void GameServer::listenForData()
{
    char buffer[1024];
    int bytesReceived;

    while (connected.load())
    {
        bytesReceived = recv(webSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived > 0)
        {
            buffer[bytesReceived] = '\0';
			std::string data(buffer, bytesReceived);
            Print(LUA, "Received from webserver: " + data);
        }
        else if (bytesReceived == 0)
        {
            Print(LUA, "Connection closed by webserver.");
            break;
        }
        else
        {
            Error(LUA, "Error receiving data.");
            break;
        }
    }
}

void GameServer::cleanup()
{
    if (connected.load())
    {
        connected.store(false);
        CLOSE_SOCKET(webSocket);
        CLEANUP_WS;
    }
}
