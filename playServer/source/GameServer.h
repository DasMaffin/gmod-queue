#pragma once

#include "GarrysMod/Lua/Interface.h"
#include <string>
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

class GameServer
{
public:
    GameServer(const std::string& serverIP, int serverPort, const std::string& webServerIP, int webServerPort, int maxPlayers, GarrysMod::Lua::ILuaBase* lua);
    ~GameServer();

    bool connectToWebServer();
    void sendInitPackage();
    void sendNewPlayer(const std::string& player);
    void listenForData();
    void cleanup();

private:
    std::string serverIP;
    std::string webServerIP;
    int serverPort;
    int webServerPort;
    SOCKET serverSocket;
    SOCKET webSocket;
    std::atomic<bool> connected;
    GarrysMod::Lua::ILuaBase* LUA;

    int maxPlayers;
};
