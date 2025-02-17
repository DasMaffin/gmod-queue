#pragma once
#define TOOLS_H

#include <string>
#include "GarrysMod/Lua/Interface.h"

// Declare the Print function
void Print(GarrysMod::Lua::ILuaBase* LUA, const std::string& msg);
void Error(GarrysMod::Lua::ILuaBase* LUA, const std::string& msg, const int errorLevel = 1);
