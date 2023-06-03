#pragma once
#include <string>
#include<algorithm>
enum class InterfaceType { INET, LAN };

inline std::string ToUpper(std::string s) {
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c) { return std::toupper(c); }
  );
  return s;
}

struct InterfaceSettings {
  int speed{0};
  std::string mode;
  InterfaceType interface_type;
  std::string ToString() const;
};
