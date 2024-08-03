#include "json_builder.h"
#include "domain.h"
#include "ip_mask.h"
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <unordered_set>
#include <variant>

namespace builder {

void FromJsonBuilder::Parse() {
  try {
    document_ = json::parse(in_);
  } catch (std::exception &e) {
    using namespace std::string_literals;
    std::cout << e.what() << '-' << boost::to_upper_copy("bad json parse\n"s);
  }
}

settings::Settings FromJsonBuilder::MakeSettings() {

  settings::Settings settings;

  if (document_.is_null()) {
    Parse();
  }

  if (const auto it = document_.find("devicenumber"); it != document_.end()) {
    settings.devicenumber = it->get<int>();
  }
  if (const auto it = document_.find("internal"); it != document_.end()) {
    settings.internal_abonent_ = GetInternalAbonent(*it);
  }
  if (const auto it = document_.find("abonents"); it != document_.end()) {
    settings.abonents_ = GetAbonents(*it);
  }

  if (const auto it = document_.find("arp"); it != document_.end()) {
    settings.arp_addresses_ = GetArpAddresses(*it);
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

  return settings;
}

std::vector<abonent::AbonentRemote>
FromJsonBuilder::GetAbonents(const json &obj) {
  using namespace std::string_literals;

  std::vector<abonent::AbonentRemote> abonents;
  abonents.reserve(obj.size());
  std::unordered_set<std::string> unique_ip_addresses;

  for (const auto &[key, value] : obj.items()) {

    network::IP_Mask mask = GetNetworkMask(value);
    std::string ip_addres = value["addres"s].get<std::string>();
    std::optional<std::string> descrip = GetAbonentDescription(value);

    auto [addres_val, is_inserted] =
        unique_ip_addresses.insert(std::move(ip_addres));
    if (!is_inserted) {
      throw std::logic_error(detail::JoinWithSeparatorWiteSpace(
          "IP address"s, *addres_val, "whith description -"s,
          descrip ? *descrip : ""s, "is allready exists"s));
    }
    abonents.emplace_back(std::move(*addres_val), std::move(mask),
                          value["number"s].get<int>(), std::move(descrip));
  }
  std::sort(
      abonents.begin(), abonents.end(),
      [](const abonent::AbonentRemote &lhs, const abonent::AbonentRemote &rhs) {
        return lhs.Number() < rhs.Number();
      });

  return abonents;
}

std::vector<network::ArpAddress>
FromJsonBuilder::GetArpAddresses(const json &obj) {

  std::vector<network::ArpAddress> arp_addresses;
  arp_addresses.reserve(obj.size());

  for (const auto &[key, value] : obj.items()) {

    network::ArpAddress arp_address(value["number"].get<int>(),
                                    value["arp_addres"].get<std::string>());

    arp_addresses.push_back(std::move(arp_address));
  }
  return arp_addresses;
}

InterfaceSettings FromJsonBuilder::GetInterfaceSettings(const json &obj) {

  InterfaceType type = obj["type"].get<std::string>() == "LAN"
                           ? InterfaceType::LAN
                           : InterfaceType::INET;

  return {obj["speed"].get<int>(), obj["mode"].get<std::string>(), type};
}

abonent::Abonent FromJsonBuilder::GetInternalAbonent(const json &obj) {
  network::IP_Mask mask = GetNetworkMask(obj);
  abonent::Abonent abonent(obj["addres"].get<std::string>(), mask);
  return abonent;
}

network::IP_Mask FromJsonBuilder::GetNetworkMask(const json &obj) {
  if (obj["mask"].is_string())
    return network::IP_Mask(obj["mask"].get<std::string>());
  return network::IP_Mask(static_cast<std::uint8_t>(obj["mask"].get<int>()));
}

std::optional<std::string>
FromJsonBuilder::GetAbonentDescription(const json &obj) {

  if (const auto desript = obj.find("description"); desript != obj.end()) {
    if (desript->is_null())
      return std::nullopt;
    else if (desript->is_string())
      return desript->get<std::string>();
    else
      throw std::logic_error("Description must be string or null");
  }
  return std::nullopt;
}

} // namespace builder
