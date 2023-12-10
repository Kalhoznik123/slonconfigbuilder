#include <iostream>
#include <type_traits>
#include <variant>
#include <boost/algorithm/string.hpp>
#include "json_builder.h"
#include "domain.h"
#include "ip_mask.h"

namespace builder{
void FromJsonBuilder::Parse() {
    try{
        document_ = json::parse(in_);
    }  catch (std::exception& e) {
        using namespace std::string_literals;

        std::cout <<e.what() << '-' << boost::to_upper_copy("bad json parse\n"s);
    }
}

settings::Settings FromJsonBuilder::MakeSettings() {

    settings::Settings settings;

    if (document_.is_null()) {
        Parse();
    }

    if (const auto it = document_.find("devicenumber");it != document_.end()) {
        settings.devicenumber = it->get<int>();
    }else{
        throw std::logic_error("missing devicenumber");
    }
    if (const auto it = document_.find("internal"); it != document_.end()) {
        settings.internal_abonent_ = GetInternalAbonent(*it);
    }else{
        throw std::logic_error("missing internal");
    }
    if (const auto it = document_.find("abonents"); it != document_.end()) {
        settings.abonents_ = GetAbonents(*it);
    }else{
        throw std::logic_error("missing abonents");
    }

    if (const auto it = document_.find("arp"); it != document_.end()) {
        settings.arp_addresses_ = GetArpAddresses(*it);
    }else{
        throw std::logic_error("missing arp");
    }
    if (const auto it = document_.find("lan"); it != document_.end()) {
        settings.lan_settings = GetInterfaceSettings(*it);
    }else{
        throw std::logic_error("missing lan");
    }

    if (const auto it = document_.find("inet"); it != document_.end()) {
        settings.inet_settings = GetInterfaceSettings(*it);
    }else{
        throw std::logic_error("missing inet");
    }

    if (const auto it = document_.find("time"); it != document_.end()) {
        settings.time = it->get<std::uint8_t>();
    }

    if (const auto it = document_.find("protocol"); it != document_.end()) {
        settings.protocol = it->get<std::uint8_t>();
    }


    return settings;
}

std::vector<abonent::AbonentRemote> FromJsonBuilder::GetAbonents(const json& obj) {

    std::vector<abonent::AbonentRemote> abonents;
    abonents.reserve(obj.size());

    for (const auto& [key, value] : obj.items()) {
        network::IP_Mask mask;

        if (value["mask"].is_string()) {
            mask.Mask(value["mask"].get<std::string>());
        } else {
            mask.Mask(static_cast<std::uint8_t>(value["mask"].get<int>()));
        }

        abonents.emplace_back(value["address"].get<std::string>(),
                mask, value["number"].get<int>());
    }

    return abonents;
}

std::vector<network::ArpAddress> FromJsonBuilder::GetArpAddresses(const json& obj) {

    std::vector<network::ArpAddress> arp_addresses;
    arp_addresses.reserve(obj.size());

    for (const auto& [key, value] : obj.items()) {

        network::ArpAddress arp_address(value["number"].get<int>(),
                value["arp_address"].get<std::string>());

        arp_addresses.push_back(std::move(arp_address));
    }
    return arp_addresses;
}

InterfaceSettings FromJsonBuilder::GetInterfaceSettings(const json& obj) {

    InterfaceType type = obj["type"].get<std::string>() == "LAN"
            ? InterfaceType::LAN
            : InterfaceType::INET;

    return {obj["speed"].get<int>(), obj["mode"].get<std::string>(), type};
}

abonent::Abonent FromJsonBuilder::GetInternalAbonent(const json& obj) {
    network::IP_Mask mask;
    if (obj["mask"].is_string()) {

        mask.Mask(obj["mask"].get<std::string>());

    }else{
        mask.Mask(static_cast<std::uint8_t>(obj["mask"].get<int>()));
    }

    abonent::Abonent abonent(obj["address"].get<std::string>(), mask);

    return abonent;
}
}
