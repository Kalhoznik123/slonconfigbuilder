#include "interface_settings.h"
#include <sstream>

std::string InterfaceSettings::ToString() const {
  std::stringstream stream;

  stream << speed << ToUpper(mode);

  return stream.str();
}
