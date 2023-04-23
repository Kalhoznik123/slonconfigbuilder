#pragma once
#include "abonent.h"
#include "arp.h"
#include "domain.h"
#include <optional>
#include <vector>

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

// template <typename CommandObject>
// std:: string MakeObjectString(const std::string command_prefix, CommandObject object){

//   std::stringstream stream;

//   bool is_first = true;

//   for (const ArpAddress& address : settings_.arp_abonents_) {

//     const std::string command_prefix = "ARP ADD ";

//     // stream << command_prefix;

//     if (is_first) {
//       stream << command_prefix << address.ToString();
//       is_first = false;
//       continue;
//     }

//     stream << '\n' << command_prefix << address.ToString();
//   }

//   return stream.str();


// }



  settings::Settings settings_;
};