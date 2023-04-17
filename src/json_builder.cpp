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

    Abonent abonent(it->at("address").get<std::string>(),
                    it->at("mask").get<int>());

    settings.internal_abonent_ = std::move(abonent);
  }
  if (const auto it = document_.find("abonents"); it != document_.end()) {

    settings.abonents_ = GetAbonents(*it);
  }

  if (const auto it = document_.find("arp"); it != document_.end()) {

    settings.arp_abonents_ = GetArpAddresses(*it);
  }

  return settings::Settings();
}

std::vector<Abonent> JsonBuilder::GetAbonents(const json& obj) {

  std::vector<Abonent> abonents;
  abonents.reserve(obj.size());

  for (const auto& [key, value] : obj.items()) {

    std::cout << value << std::endl;

    Abonent abonent(value["address"].get<std::string>(),
                    value["mask"].get<int>(), value["number"].get<int>());

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