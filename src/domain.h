#pragma once
#include "abonent.h"
#include "arp.h"
#include <optional>
#include <vector>

struct Settings {

  std::vector<Abonent> abonents_;
  std::vector<ArpAdress> arp_abonents_;
  std::optional<std::uint8_t> time;
  std::optional<std::uint8_t> protocol;
  Abonent internal_abonent_;
};
