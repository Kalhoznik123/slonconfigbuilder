#include <sstream>
#include "arp.h"

std::string ArpAddress::Address() const noexcept{ return arp_address_.Address(); }

int ArpAddress::Number() const noexcept{ return number_; }

std::string ArpAddress::ToString() const {

  std::stringstream str_stream;

  str_stream << number_ << " " << Address();

  return str_stream.str();
}
