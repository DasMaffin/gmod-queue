#include "Message.h"
#include "tools.h"
#include <iostream>

// Constructor
Message::Message(const std::string& msg, const std::string& time, GarrysMod::Lua::ILuaBase* lua)
    : message(msg), timestamp(time), LUA(lua) {
}

// Print the message and elapsed time
void Message::print() const {
    Print(LUA, "Message: " + message + "\nTimestamp: " + timestamp);
}
