#include "ip_address.h"

void IP_addres::Address(std::string_view ip_address) {
  addres_ = boost::asio::ip::address_v4::from_string(std::string(ip_address));
}

std::string IP_addres::Address() const { return addres_.to_string(); }
