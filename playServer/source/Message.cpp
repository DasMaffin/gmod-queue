#include "Message.h"
#include <iostream>

// Constructor
Message::Message(const std::string& msg, const std::string& time, GarrysMod::Lua::ILuaBase* lua)
    : message(msg), timestamp(time), LUA(lua) {
}

// Print the message and elapsed time
void Message::print() const {
    //Print("Message: " + message + "\nTimestamp: " + timestamp)
}
