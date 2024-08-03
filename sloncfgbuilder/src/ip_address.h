#pragma once
#include <boost/asio/ip/address_v4.hpp>
#include <string>
#include <string_view>

class IP_addres {
public:
  IP_addres() = default;
  IP_addres(const IP_addres &rhs) : addres_(rhs.addres_){};
  IP_addres(IP_addres &&rhs) noexcept : addres_(std::move(rhs.addres_)){};
  IP_addres(std::string_view ip_address)
      : addres_(
            boost::asio::ip::address_v4::from_string(std::string(ip_address))) {
  }
  ~IP_addres() = default;

  IP_addres &operator=(const IP_addres &rhs) {
    addres_ = rhs.addres_;
    return *this;
  }

  IP_addres &operator=(IP_addres &&rhs) noexcept {
    addres_ = std::move(rhs.addres_);
    return *this;
  }

  void Address(std::string_view ip_address);
  std::string Address() const;

private:
  boost::asio::ip::address_v4 addres_;
};
