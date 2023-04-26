#pragma once
#include <string>
#include "ARP.h"

class ArpAddress {

public:
 // ArpAddress() = default;

  ArpAddress(std::uint8_t number, const std::string& arp_address)
      : number_(number), arp_address_(network::ARP(arp_address)) {}

  std::string Address() const;

  int Number() const;

  std::string ToString() const;

private:
  int number_;
  network::ARP arp_address_;
};