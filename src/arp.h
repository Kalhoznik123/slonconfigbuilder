#pragma once
#include <string>

class ArpAddress {

public:
 ArpAddress() = default;
 
 
  ArpAddress(std::uint8_t number, const std::string& arp_address)
      : number_(number), arp_address_(arp_address) {}

private:
  std::uint8_t number_;
  std::string arp_address_;
};