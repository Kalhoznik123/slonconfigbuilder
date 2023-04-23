#include "arp.h"
#include <sstream>

std::string ArpAddress::Address() const { return arp_address_; }

int ArpAddress::Number() const { return number_; }

std::string ArpAddress::ToString() const {

  std::stringstream str_stream;

  str_stream << number_ << " " << arp_address_;

  return str_stream.str();
}
