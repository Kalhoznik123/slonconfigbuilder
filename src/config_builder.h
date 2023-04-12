#pragma once
#include "abonent.h"
#include "arp.h"
#include <vector>
#include <optional>

class ConfigBuilder{
  public:



  private:

std::vector<Abonent> abonents_;
std::vector<ArpAdress> arp_abonents_;
std::optional<std::uint8_t> time{0};
std::optional<std::uint8_t> protocol{0};
Abonent internal_abonent_;

};