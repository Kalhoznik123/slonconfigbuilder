#include "cin_builder.h"
#include "arp.h"
#include "abonent_remote.h"
#include "parsers.h"
#include <cstdint>
#include <string>
#include <cstdint>
#include <boost/variant.hpp>
#include <regex>

namespace client {

void RestoreStream(std::istream& in){
    in.ignore();
    in.clear();
}


bool IsIpAddressValid(const std::string& ip_addr ){

    // Regex expression for validating IPv4
    std::regex ipv4("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");

    return regex_match(ip_addr, ipv4);
}


network::IP_Mask MakeMaskFromVariant(const boost::variant<std::string,int>& parsed_mask){
    network::IP_Mask ip_mask;
    if(const auto* res_i = boost::get<int>(&parsed_mask);res_i){
        ip_mask.Mask(static_cast<std::uint8_t>(*res_i));
    }else{
        const auto* res_str = boost::get<std::string>(&parsed_mask);
        ip_mask.Mask(*res_str);
    }
    return ip_mask;
}
}


namespace builder{


std::optional<InterfaceSettings> CommonInterfaceSettings(InterfaceType type){
    std::string user_input;

    while(getline(std::cin,user_input) ){
        namespace interface = parsers::interface_parser;

        if(user_input.empty()){
            client::RestoreStream(std::cin);
            break;
        }
        interface::InterfaceParseRes pars_result;

        bool ok = interface::parse(user_input,pars_result);

        if(ok){
            //TODO::ДОБАВТЬ ПРОВЕРКУ ВАЛИДНОСТИ ВСКОРОСТИ И РЕЖИМА РАБОТЫ
            client::RestoreStream(std::cin);

            InterfaceSettings settings = {pars_result.speed, pars_result.mode, type};
            std::optional<InterfaceSettings> result = std::move(settings);
            return result;
        }else
            client::RestoreStream(std::cin);

    }

    return  std::nullopt;


}





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

    std::string user_input;

    while(getline(std::cin,user_input) ){

        namespace intern_abon = parsers::internal_abonent_parser;

        if(user_input.empty()){
            client::RestoreStream(std::cin);
            break;
        }

        intern_abon::IAbonentParseRes parser_result;

        bool ok = intern_abon::parse(user_input,parser_result);
        if(ok){

            if(client::IsIpAddressValid(parser_result.ip_address)){
                network::IP_Mask mask = client::MakeMaskFromVariant(parser_result.mask);
                client::RestoreStream(std::cin);
                return abonent::Abonent(parser_result.ip_address,mask);
            }else
                continue;
        }else
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

std::optional<std::vector<abonent::AbonentRemote>> FromCinBuilder::MakeRemoteAbonents() {

    size_t count{0};
    in_ >> count;

    if(count == 0){
        return std::nullopt;
    }

    std::vector<abonent::AbonentRemote> abonents;
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

std::optional<std::vector<network::ArpAddress>> FromCinBuilder::MakeArpAddresses() {

    size_t count{0};
    in_ >> count;

    if(count == 0){
        return std::nullopt;
    }

    std::vector<network::ArpAddress> arp_addresses;
    arp_addresses.reserve(count);

    for (size_t i = 0; i < count; ++i) {
        int number{0};
        std::string arp_address;
        in_ >> number >> arp_address;
        arp_addresses.emplace_back(number, arp_address);
    }

    return arp_addresses;
}

std::optional<std::uint8_t> FromCinBuilder::MakeTime() {
    int time{0};
    in_ >> time;

    if(time == 0){
        return std::nullopt;
    }

    return static_cast<std::uint8_t>(time);
}

std::optional<int> FromCinBuilder::MakeDevicenumber() {
    int device_number{0};
    in_ >> device_number;

    if(device_number == 0){
        return std::nullopt;
    }

    return device_number;
}

std::optional<std::uint8_t> FromCinBuilder::MakeProtocol() {
    int protocol{0};
    in_ >> protocol;

    if(protocol == 0){
        return std::nullopt;
    }

    return static_cast<std::uint8_t>(protocol);
}
}
