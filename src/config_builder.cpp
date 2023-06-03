#include <sstream>
#include <string>
#include "config_builder.h"

namespace configurator {

std::string ConfigBuilder::Dump() const {

  std::stringstream stream;

  const std::string update_command = "UPDATE";




  stream << MakeDevicenumber() << "\n";
  stream << MakeAbonentString(settings_.internal_abonent_) << "\n";
  stream << MakeAbonentsString() << "\n";
  stream << MakeArpAddressesString() << "\n";
  stream << MakeInterfaceString(settings_.lan_settings) << std::endl;
  stream << MakeInterfaceString(settings_.inet_settings) << "\n";
  stream << MakeTimetoliveString() << "\n";
  stream << MakeProtocolString() << "\n";
  stream << update_command;

  return stream.str();
}

std::string ConfigBuilder::MakeDevicenumber() const {

  std::stringstream stream;

  stream << "DEVICENUMBER" << ' ' << *settings_.devicenumber;

  return stream.str();
}
std::string ConfigBuilder::MakeAbonentString(const Abonent& abonent) {

  std::stringstream stream;

  stream << "ABONENT ADD ";

  stream << (abonent.AbonType() == AbonentType::INTERNAL ? "INTERNAL " : "");

  stream << abonent.ToString();

  return stream.str();
}

std::string ConfigBuilder::MakeAprString(const ArpAddress& arp_address){

  std::stringstream stream;

  stream << "ARP ADD " << arp_address.ToString();

  return stream.str();
}

std::string
ConfigBuilder::MakeInterfaceString(const InterfaceSettings& settings){
  std::stringstream stream;
  stream << "IFCONFIG ";

  stream << (settings.interface_type == InterfaceType::LAN ? "LAN " : "INET ");

  stream << settings.ToString();

  return stream.str();
}

std::string ConfigBuilder::MakeTimetoliveString() const{

  const std::string time =
      settings_.time ? std::to_string(*settings_.time) : "80";

  const std::string result = "TIMETOLIVE " + time;
  return result;
}

std::string ConfigBuilder::MakeProtocolString() const{

  const std::string protocol =
      settings_.protocol ? std::to_string(*settings_.protocol) : "53";
  const std::string result = "PROTOCOL " + protocol;

  return result;
}

std::string ConfigBuilder::MakeAbonentsString() const{

  std::stringstream stream;

  bool is_first = true;

  for (const Abonent& abonent : settings_.abonents_) {

    if (is_first) {
      stream << MakeAbonentString(abonent);
      is_first = false;
      continue;
    }

    stream << '\n' << MakeAbonentString(abonent);
  }

  return stream.str();
}

std::string ConfigBuilder::MakeArpAddressesString() const{

  std::stringstream stream;

  bool is_first = true;

  for (const ArpAddress& address : settings_.arp_addresses_) {

    if (is_first) {
      stream << MakeAprString(address);
      is_first = false;
      continue;
    }

    stream << '\n' << MakeAprString(address);
  }

  return stream.str();
}
} // namespace configurator