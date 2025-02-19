#include "GameServer.h"
#include "tools.h"
#include <thread>
#include <string>

GameServer::GameServer(const std::string& serverIP, int serverPort, const std::string& webServerIP, int webServerPort, GarrysMod::Lua::ILuaBase* lua)
    : serverIP(serverIP), serverPort(serverPort), webServerIP(webServerIP), webServerPort(webServerPort), serverSocket(INVALID_SOCKET), webSocket(INVALID_SOCKET), connected(false), LUA(lua)
{
    // Initialize Winsock (if needed)
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

    // Send the initial data
    sendInitPackage();

    // Start listening for data
    std::thread listenerThread(&GameServer::listenForData, this);
    listenerThread.detach();  // Detach so it runs in the background

    return true;
}

void GameServer::sendInitPackage()
{
    if (!connected.load())
    {
        Error(LUA, "Not connected to web server.");
        return;
    }

    // Example initialization data: Server IP, Max Players, etc.
    std::string initData = "{ \"serverIP\": \"" + serverIP + "\", \"maxPlayers\": 10, \"isQueueServer\": false }";
    send(webSocket, initData.c_str(), initData.size(), 0);
    Print(LUA, "Sent initialization data: " + initData);
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
            buffer[bytesReceived] = '\0';  // Null-terminate the received data
            Print(LUA, "Received from webserver: " + std::string(buffer, sizeof(buffer)));  // Print received data to Lua
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

        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Prevent high CPU usage
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
