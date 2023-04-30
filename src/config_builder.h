#pragma once
#include "abonent.h"
#include "arp.h"
#include "domain.h"
#include <optional>
#include <vector>

namespace configurator {

class ConfigBuilder {
public:
  ConfigBuilder() = default;
  ConfigBuilder(const settings::Settings& settings)
      : settings_(settings){

        };

  std::string Dump();

private:
  std::string MakeDevicenumber();
  static std::string MakeAbonentString(const Abonent& abonent);
  static std::string MakeAprString(const ArpAddress& arp_address);
  static std::string MakeInterfaceString(const InterfaceSettings& settings);
  std::string MakeTimetoliveString();
  std::string MakeProtocolString();

  std::string MakeAbonentsString();
  std::string MakeArpAddressesString();

  settings::Settings settings_;
};

} // namespace configurator