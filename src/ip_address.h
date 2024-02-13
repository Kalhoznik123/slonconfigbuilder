#pragma once
#include <string>
#include <string_view>
#include <boost/asio/ip/address_v4.hpp>

class IP_address
{
public:

IP_address() = default;
IP_address(const IP_address& rhs) = default;
IP_address(std::string_view ip_address)
    :address_(boost::asio::ip::address_v4::from_string(std::string(ip_address))){ }

void Address(std::string_view ip_address);
std::string Address() const;

private:
boost::asio::ip::address_v4 address_;
};


