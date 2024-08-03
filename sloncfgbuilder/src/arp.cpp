#include <sstream>
#include "arp.h"
#include "detail.h"

namespace network {
using namespace std::string_literals;
std::string ArpAddress::Address() const noexcept{ return arp_address_.Address(); }

int ArpAddress::Number() const noexcept{ return number_; }

std::string ArpAddress::ToString() const {    
    std::string res = detail::JoinWithSeparatorWiteSpace(std::to_string(number_),Address());
  return res;
}
}
