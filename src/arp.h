#pragma once
#include <string>

class ArpAddress {

public:
  ArpAddress() = default;

  ArpAddress(std::uint8_t number, const std::string& arp_address)
      : number_(number), arp_address_(arp_address) {}

  std::string Address() const;

  std::uint8_t Number() const;

  std::string ToString() const;

private:
  std::uint8_t number_;
  std::string arp_address_;
};