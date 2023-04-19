#pragma once
#include <string>


struct InterfaceSettings
{
std::uint8_t speed{0};
std::string mode;

std::string ToString() const;

};
