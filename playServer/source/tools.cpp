#include "tools.h"

// Implement the Print function
void Print(GarrysMod::Lua::ILuaBase* LUA, const std::string& msg)
{
    LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
    LUA->GetField(-1, "print");
    LUA->PushString(msg.c_str());
    LUA->Call(1, 0);
    LUA->Pop();
}

void Error(GarrysMod::Lua::ILuaBase* LUA, const std::string& msg, const int errorLevel) 
{
    LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
    LUA->GetField(-1, "error");
    LUA->PushString(msg.c_str());
    LUA->PushNumber(errorLevel);
    LUA->Call(2, 0);
    LUA->Pop();
}
