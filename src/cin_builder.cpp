#include "cin_builder.h"
#include "arp.h"
#include "abonent_remote.h"
#include <cstdint>
#include <string>
#include <cstdint>

settings::Settings FromCinBuilder::MakeSettings() {

  using namespace std::string_literals;
  // TODO: сделать mode как отдельный класс с проверкой на правильность
  settings::Settings settings;

  std::cout << "Enter internal abonent(ip address/mask): ";
  settings.internal_abonent_ = MakeInternalAbonent();
  std::cout << "Enter lan settings(speed/mode(HD or FD)): ";
  settings.lan_settings = MakeLanSettings();
  std::cout << "Enter inet settings(speed/mode(HD or FD)): ";
  settings.inet_settings = MakeInetSettings();
  std::cout << "Enter abonents (cout/Abonent(devicenumber/ip_address/mask)): ";
  settings.abonents_ = MakeAbonents();
  std::cout << "Enter arp addresses (cout/Arp abonent(number/arp_address)): ";
  settings.arp_addresses_ = MakeArpAddresses();
  std::cout << "Enter time: ";
  settings.time = MakeTime();
  std::cout << "Enter devicenumber: ";
  settings.devicenumber = MakeDevicenumber();
  std::cout << "Enter protocol: ";
  settings.protocol = MakeProtocol();

  return settings;
}

Abonent FromCinBuilder::MakeInternalAbonent() {
  std::string ip_addres;
  int mask{0};
  in_ >> ip_addres >> mask;
  network::IP_Mask ip_mask(static_cast<std::uint8_t>(mask));
  Abonent abonent(ip_addres, ip_mask);
  return abonent;
}

InterfaceSettings FromCinBuilder::MakeLanSettings() {
  int speed{0};
  std::string mode;
  in_ >> speed >> mode;
  return {speed, mode, InterfaceType::LAN};
}

InterfaceSettings FromCinBuilder::MakeInetSettings() {
  int speed{0};
  std::string mode;
  in_ >> speed >> mode;
  return {speed, mode, InterfaceType::INET};
}

std::vector<AbonentRemote> FromCinBuilder::MakeAbonents() {
  size_t count{0};
  in_ >> count;
  std::vector<AbonentRemote> abonents;
  abonents.reserve(count);

  for (size_t i = 0; i < count; ++i) {
    int number{0};
    int mask{0};
    std::string ip_address;
    in_ >> number >> ip_address >> mask;
    network::IP_Mask ip_mask(static_cast<std::uint8_t>(mask));
    abonents.emplace_back(ip_address, ip_mask, number);
  }
  return abonents;
}

std::vector<ArpAddress> FromCinBuilder::MakeArpAddresses() {

  size_t count{0};
  in_ >> count;
  std::vector<ArpAddress> arp_addresses;
  arp_addresses.reserve(count);

  for (size_t i = 0; i < count; ++i) {
    int number{0};
    std::string arp_address;
    in_ >> number >> arp_address;
    arp_addresses.emplace_back(number, arp_address);
  }

  return arp_addresses;
}

std::uint8_t FromCinBuilder::MakeTime() {
  int time{0};
  in_ >> time;
  return static_cast<std::uint8_t>(time);
}

int FromCinBuilder::MakeDevicenumber() {
  int device_number{0};
  in_ >> device_number;
  return device_number;
}

std::uint8_t FromCinBuilder::MakeProtocol() {
  int protocol{0};
  in_ >> protocol;
  return static_cast<std::uint8_t>(protocol);
}
