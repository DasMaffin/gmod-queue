#include "GarrysMod/Lua/Interface.h"
#include "GameServer.h"
#include "tools.h"

static GameServer* gameServer = nullptr;

LUA_FUNCTION(ConnectToWebServer)
{
    // Check if the GameServer object is already created
    if (gameServer == nullptr)
    {
        // Default values
        const char* localServerIP = "";
        const char* webServerIP = "";
        int webServerPort = 8080;
		int maxPlayers = 32;

        if (LUA->IsType(1, GarrysMod::Lua::Type::STRING)) {
			localServerIP = LUA->GetString(1);
        }
        else {
			Error(LUA, "Local server IP is required.");
			return 0;
        }
        if (LUA->IsType(2, GarrysMod::Lua::Type::STRING)) {
            webServerIP = LUA->GetString(2);
        }
		else {
			Error(LUA, "Web server IP is required.");
			return 0;
		}
        if (LUA->IsType(3, GarrysMod::Lua::Type::NUMBER)) {
            webServerPort = (int)LUA->GetNumber(3);
        }
		if (LUA->IsType(4, GarrysMod::Lua::Type::NUMBER)) {
			maxPlayers = (int)LUA->GetNumber(4);
		}

        // Initialize the GameServer with the provided values
        gameServer = new GameServer(localServerIP, 8080, webServerIP, webServerPort, maxPlayers, LUA);
    }

    // Attempt to connect to the web server
    bool connected = gameServer->connectToWebServer();

    // Push the connection status as a boolean
    LUA->PushBool(connected);
    return 1;
}

LUA_FUNCTION(RegisterNewPlayer)
{
	if (gameServer != nullptr)
	{
		gameServer->sendNewPlayer(LUA->GetString(1));
		return 0;
	}
	Error(LUA, "GameServer not connected or initialized.");
	return 0;
}

LUA_FUNCTION(DisconnectWebServer)
{
	if (gameServer != nullptr)
	{
		gameServer->cleanup();
		delete gameServer;
		gameServer = nullptr;
	}
	return 0;
}

GMOD_MODULE_OPEN()
{
	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);

	LUA->PushCFunction(RegisterNewPlayer);
	LUA->SetField(-2, "RegisterNewPlayer");

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