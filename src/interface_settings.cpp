#include "interface_settings.h"
#include "domain.h"
#include <sstream>
#include <boost/algorithm/string.hpp>

std::string InterfaceSettings::ToString() const {
  std::stringstream stream;

  stream << speed <<  boost::to_upper_copy(mode);  //  ToUpper(mode);

  return stream.str();
}
