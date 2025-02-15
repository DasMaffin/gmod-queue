#pragma once
#define MESSAGE_H

#include <string>
#include "GarrysMod/Lua/Interface.h"

class Message {
public:
    std::string message;
    std::string timestamp;
    GarrysMod::Lua::ILuaBase* LUA;

    Message(const std::string& msg, const std::string& time, GarrysMod::Lua::ILuaBase* lua);
    void print() const;
};
