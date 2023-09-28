#include "interface_settings.h"
#include "domain.h"
#include <sstream>



std::string ToUpper(std::string s) {
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c) { return std::toupper(c); }
  );
  return s;
}


std::string InterfaceSettings::ToString() const {
  std::stringstream stream;

  stream << speed << ToUpper(mode);

  return stream.str();
}
