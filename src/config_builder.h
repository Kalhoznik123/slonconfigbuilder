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
std::optional<std::uint8_t> time;
std::optional<std::uint8_t> protocol;
Abonent internal_abonent_;

};