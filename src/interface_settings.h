#pragma once
#include <string>

enum class InterfaceType { INET, LAN };

struct InterfaceSettings {
  int speed{0};
  std::string mode;
  InterfaceType interface_type;
  std::string ToString() const;
};
