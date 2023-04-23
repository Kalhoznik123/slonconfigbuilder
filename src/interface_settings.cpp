#include "interface_settings.h"
#include <sstream>

std::string InterfaceSettings::ToString() const {
  std::stringstream stream;

  stream << speed << mode;

  return stream.str();
}
