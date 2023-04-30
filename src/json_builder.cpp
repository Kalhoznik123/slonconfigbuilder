#include "json_builder.h"
#include "domain.h"
#include <iostream>
#include <nlohmann/json.hpp>
void JsonBuilder::Parse() { document_ = json::parse(in_); }

settings::Settings JsonBuilder::MakeSettings() {

  settings::Settings settings;

  if (document_.is_null()) {
    Parse();
  }

  if (const auto it = document_.find("internal.address");
      it != document_.end()) {


    settings.internal_abonent_ = GetInternalAbonent(*it);
  }
  if (const auto it = document_.find("abonents"); it != document_.end()) {

    settings.abonents_ = GetAbonents(*it);
  }

  if (const auto it = document_.find("arp"); it != document_.end()) {

    settings.arp_abonents_ = GetArpAddresses(*it);
  }
  if (const auto it = document_.find("lan"); it != document_.end()) {
    settings.lan_settings = GetInterfaceSettings(*it);
  }

  if (const auto it = document_.find("inet"); it != document_.end()) {
    settings.inet_settings = GetInterfaceSettings(*it);
  }

  if (const auto it = document_.find("time"); it != document_.end()) {
    settings.time = it->get<std::uint8_t>();
  }

  if (const auto it = document_.find("protocol"); it != document_.end()) {
    settings.protocol = it->get<std::uint8_t>();
  }

  if (const auto it = document_.find("internal.number");
      it != document_.end()) {
    settings.devicenumber = it->get<int>();
  }
  return settings;
}

std::vector<Abonent> JsonBuilder::GetAbonents(const json& obj) {

  std::vector<Abonent> abonents;
  abonents.reserve(obj.size());

  for (const auto& [key, value] : obj.items()) {

    Abonent abonent(value["address"].get<std::string>(),
                    value["mask"].get<int>(), AbonentType::REMOTE,
                    value["number"].get<int>());

    abonents.push_back(std::move(abonent));
  }

  return abonents;
}

std::vector<ArpAddress> JsonBuilder::GetArpAddresses(const json& obj) {

  std::vector<ArpAddress> arp_addresses;
  arp_addresses.reserve(obj.size());

  for (const auto& [key, value] : obj.items()) {

    ArpAddress arp_address(value["number"].get<int>(),
                           value["ArpAddress"].get<std::string>());

    arp_addresses.push_back(std::move(arp_address));
  }
  return arp_addresses;
}

InterfaceSettings JsonBuilder::GetInterfaceSettings(const json& obj) {

  InterfaceType type = obj["type"].get<std::string>() == "LAN"
                           ? InterfaceType::LAN
                           : InterfaceType::INET;

  return {obj["speed"].get<int>(), obj["mode"].get<std::string>(), type};
}

Abonent JsonBuilder::GetInternalAbonent(const json& obj) {

  Abonent abonent(obj["address"].get<std::string>(), obj["mask"].get<int>(),
                  AbonentType::INTERNAL);

  return Abonent();
}
