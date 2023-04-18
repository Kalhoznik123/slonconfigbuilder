#pragma once
#include "abonent.h"
#include "arp.h"
#include "interface_settings.h"
#include <optional>
#include <vector>

namespace settings {

struct Settings {

  Abonent internal_abonent_;
  InterfaceSettings lan_settings;
  InterfaceSettings inet_settings;
  std::vector<Abonent> abonents_;
  std::vector<ArpAddress> arp_abonents_;
  std::optional<std::uint8_t> time;
  std::optional<std::uint8_t> devicenumber;
  std::optional<std::uint8_t> protocol;
};
} // namespace settings