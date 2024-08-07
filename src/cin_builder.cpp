#include "cin_builder.h"
#include "abonent_remote.h"
#include "arp.h"
#include "parsers.h"
#include <boost/lexical_cast.hpp>
#include <boost/variant.hpp>
#include <cstdint>
#include <regex>
#include <string>

namespace client {

void RestoreStream(std::istream &in) { in.clear(); }

bool IsIpAddressValid(const std::string &ip_addr) {

  // Regex expression for validating IPv4
  std::regex ipv4("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}(["
                  "0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");
  return regex_match(ip_addr, ipv4);
}

network::IP_Mask
MakeMaskFromVariant(const boost::variant<std::string, int> &parsed_mask) {
  network::IP_Mask ip_mask;
  if (const auto *res_i = boost::get<int>(&parsed_mask); res_i) {
    ip_mask.Mask(static_cast<std::uint8_t>(*res_i));
  } else {
    const auto *res_str = boost::get<std::string>(&parsed_mask);
    ip_mask.Mask(*res_str);
  }
  return ip_mask;
}

template <typename Comparator>
std::optional<std::uint8_t> GetUIntFromStr(Comparator cmp) {
  std::string user_input;
  client::RestoreStream(std::cin);

  while (std::getline(std::cin, user_input)) {
    if (user_input.empty()) {
      client::RestoreStream(std::cin);
      break;
    }
    std::uint8_t res{0};
    const bool ok = boost::conversion::try_lexical_convert(user_input, res);
    if (ok) {
      if (cmp(res)) {
        client::RestoreStream(std::cin);
        return res;
      }
    }
  }
  return std::nullopt;
}

void AddRemoteAbonentFromStr(std::vector<abonent::AbonentRemote> abonents,
                             std::string &str) {

  while (std::getline(std::cin, str)) {

    if (str.empty()) {
      client::RestoreStream(std::cin);
      return;
    }

    using RAbonentParserRes_t =
        parsers::remote_abonent_parser::RAbonentParseRes;
    using RemoteAbonentParser_t =
        parsers::remote_abonent_parser::remote_abonent_parser<
            std::string::const_iterator>;
    RAbonentParserRes_t parse_res;

    bool ok = parsers::Parse<RemoteAbonentParser_t>(str, parse_res);
    if (ok) {
      if (client::IsIpAddressValid(parse_res.ip_address)) {
        abonents.emplace_back(parse_res.ip_address,
                              client::MakeMaskFromVariant(parse_res.mask),
                              parse_res.devicenumber);
        client::RestoreStream(std::cin);
        return;
      }
    } else {
      client::RestoreStream(std::cin);
    }
  }
}

void AddARPAddressFromStr(std::vector<network::ArpAddress> arp_addresses,
                          std::string &str) {
  while (std::getline(std::cin, str)) {

    if (str.empty()) {
      client::RestoreStream(std::cin);
      return;
    }
    using ARPAddressPaseRes_t = parsers::ARP_address_parser::ARPAddressParseRes;
    using ARPAddressParser_t = parsers::ARP_address_parser::ARP_address_parser<
        std::string::const_iterator>;

    ARPAddressPaseRes_t parse_res;

    bool ok = parsers::Parse<ARPAddressParser_t>(str, parse_res);
    if (ok) {
      arp_addresses.emplace_back(parse_res.number, parse_res.ARP_address);
      client::RestoreStream(std::cin);
      return;
    }
    client::RestoreStream(std::cin);
  }
}
} // namespace client

namespace builder {

bool SpeedValidation(std::uint8_t speed) {
 const size_t min_speed = 0;
 const size_t max_speed  = 100;
  return (speed >= min_speed) && (speed <= max_speed);
}

bool ModeValidation(const std::string &mode) {
  return (mode == "FD") || (mode == "HD");
}

std::optional<InterfaceSettings> CommonInterfaceSettings(InterfaceType type) {

  using interface_parser =
      parsers::interface_parser::interface_parser<std::string::const_iterator>;
  std::string user_input;

  while (std::getline(std::cin, user_input)) {
    namespace interface = parsers::interface_parser;

    if (user_input.empty()) {
      client::RestoreStream(std::cin);
      break;
    }
    interface::InterfaceParseRes pars_result;

    bool ok = parsers::Parse<interface_parser>(user_input, pars_result);

    if (ok) {
      if (SpeedValidation(pars_result.speed) &&
          ModeValidation(pars_result.mode)) {
        client::RestoreStream(std::cin);
        InterfaceSettings settings = {pars_result.speed, pars_result.mode,
                                      type};
        std::optional<InterfaceSettings> result = std::move(settings);
        return result;
      }
      client::RestoreStream(std::cin);
      continue;
    }
    client::RestoreStream(std::cin);
  }
  return std::nullopt;
}

settings::Settings FromCinBuilder::MakeSettings() {

  using namespace std::string_literals;

  settings::Settings settings;
  std::cout << "Enter internal abonent(ip address/mask): ";
  settings.internal_abonent_ = MakeInternalAbonent();
  std::cout << "Enter lan settings(speed/mode(HD or FD)): ";
  settings.lan_settings = MakeLanSettings();
  std::cout << "Enter inet settings(speed/mode(HD or FD)): ";
  settings.inet_settings = MakeInetSettings();
  std::cout << "Enter abonents (cout/Abonent(devicenumber/ip_address/mask)): ";
  settings.abonents_ = MakeRemoteAbonents();
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

std::optional<abonent::Abonent> FromCinBuilder::MakeInternalAbonent() {

  using internal_parser =
      parsers::internal_abonent_parser::internal_abonent_parser<
          std::string::const_iterator>;

  std::string user_input;

  while (std::getline(std::cin, user_input)) {
    namespace intern_abon = parsers::internal_abonent_parser;
    if (user_input.empty()) {
      client::RestoreStream(std::cin);
      break;
    }
    intern_abon::IAbonentParseRes parser_result;

    bool ok = parsers::Parse<internal_parser>(user_input, parser_result);

    if (ok) {
      if (client::IsIpAddressValid(parser_result.ip_address)) {
        network::IP_Mask mask = client::MakeMaskFromVariant(parser_result.mask);
        client::RestoreStream(std::cin);
        return abonent::Abonent(parser_result.ip_address, mask);
      }
      client::RestoreStream(std::cin);
      continue;
    }
    client::RestoreStream(std::cin);
  }
  return std::nullopt;
}

std::optional<InterfaceSettings> FromCinBuilder::MakeLanSettings() {
  return CommonInterfaceSettings(InterfaceType::LAN);
}

std::optional<InterfaceSettings> FromCinBuilder::MakeInetSettings() {
  return CommonInterfaceSettings(InterfaceType::INET);
}

std::optional<std::vector<abonent::AbonentRemote>>
FromCinBuilder::MakeRemoteAbonents() {

  int abon_count{0};
  std::cin >> abon_count;
  client::RestoreStream(std::cin);
  std::vector<abonent::AbonentRemote> abonents;
  abonents.reserve(abon_count);
  std::cin.get();
  std::string user_input;
  for (size_t i = 0; i < abon_count; ++i) {
    client::AddRemoteAbonentFromStr(abonents, user_input);
  }
  return abon_count || abonents.empty() ? std::nullopt
                                        : std::optional(abonents);
}

std::optional<std::vector<network::ArpAddress>>
FromCinBuilder::MakeArpAddresses() {

  // ввод адреса будет только сплошным текстом
  size_t count{0};
  in_ >> count;
  client::RestoreStream(std::cin);
  std::vector<network::ArpAddress> arp_addresses;
  std::cin.get();
  arp_addresses.reserve(count);
  std::string user_input;

  for (int i = 0; i < count; ++i) {
    client::AddARPAddressFromStr(arp_addresses, user_input);
  }
  return count || arp_addresses.empty() ? std::nullopt
                                        : std::optional(arp_addresses);
}

std::optional<std::uint8_t> FromCinBuilder::MakeTime() {
  const std::uint8_t time_val = 80;
  return client::GetUIntFromStr([](std::uint8_t val) { return val <= time_val; });
}

std::optional<std::uint8_t> FromCinBuilder::MakeDevicenumber() {
  const std::uint8_t dev_num_protocol = 99;
  return client::GetUIntFromStr([](std::uint8_t val) { return val <= dev_num_protocol; });
}

std::optional<std::uint8_t> FromCinBuilder::MakeProtocol() {
  const std::uint8_t max_protocol_num = 99;
  return client::GetUIntFromStr([](std::uint8_t val) { return val <= max_protocol_num; });
}
} // namespace builder
