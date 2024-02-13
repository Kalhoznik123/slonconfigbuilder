#include "ip_address.h"

void IP_address::Address(std::string_view ip_address){
    address_ = boost::asio::ip::address_v4::from_string(std::string(ip_address));
}

std::string IP_address::Address() const{

    return address_.to_string();
}
