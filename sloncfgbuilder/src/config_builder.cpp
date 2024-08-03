
#include <string>
#include <sstream>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include "domain.h"
#include "abonent_remote.h"
#include "config_builder.h"

namespace configurator {
using namespace std::string_literals;

std::string ConfigBuilder::Dump() const {

   auto res = detail::Join(std::string("\n"),
                            MakeDevicenumber(),
                            MakeAbonentString(settings_.internal_abonent_),
                            MakeAbonentsString(settings_.abonents_),
                            MakeArpAddressesString(settings_.arp_addresses_),
                            MakeInterfaceString(settings_.lan_settings),
                            MakeInterfaceString(settings_.inet_settings),
                            MakeTimetoliveString(),
                            MakeProtocolString(),
                            "UPDATE"s
                            );
    return res;
}

std::vector<std::string> ConfigBuilder::MakeDescriptions() const{

    if(!settings_.abonents_.has_value())
        return {};

    if(abonents_descriptions_.has_value()){    //для кеширования
        return *abonents_descriptions_;
    }

    std::vector<std::string> result;
    result.reserve(settings_.abonents_->size());

    for(auto& abonent: *settings_.abonents_){
        if(abonent.Description().has_value())
            result.push_back(*abonent.Description());
    }
    abonents_descriptions_ = result;

    return result;
}

std::string ConfigBuilder::MakeDevicenumber() const {
    std::string res;
    if(settings_.devicenumber.has_value()){
        res = detail::Join(" "s,"DEVICENUMBER"s,
                           std::to_string(*settings_.devicenumber));
    }
    return  res;
}

std::string ConfigBuilder::MakeAbonentString(const std::optional<abonent::Abonent>& abonent) {
    std::string res;
    if(abonent.has_value()){
        res = detail::JoinWithSeparatorWiteSpace("ABONENT ADD INTERNAL"s,
                                                 abonent->Ip_addres(),
                                                 std::to_string(abonent->Mask().ShortRecord())
                                                 );
    }

    return  res;
}

std::string ConfigBuilder::MakeAbonentsString(const std::optional<std::vector<abonent::AbonentRemote>>& abonents){

    std::string res;
    if(abonents.has_value()){
        res = CommonObjContainerStringMaker(abonents,&MakeAbonentRemoteString);

    }
    return res;
}

std::string ConfigBuilder::MakeArpAddressesString(const std::optional<std::vector<network::ArpAddress>>& arp_adresses) const{
    std::string res;
    if(arp_adresses.has_value()){
        res = CommonObjContainerStringMaker(arp_adresses,&MakeAprString);
    }
    return res;
}

std::string ConfigBuilder::MakeInterfaceString(const std::optional<InterfaceSettings>& interface_settings){
    std::string res;
    if(interface_settings.has_value()){
        std::string interface_type = interface_settings->interface_type == InterfaceType::LAN ? "LAN"s : "INET"s;
        res = detail::Join(" "s,"IFCONFIG"s,
                           std::move(interface_type),
                           std::to_string(interface_settings->speed) + interface_settings->mode
                           );
    }
    return  res;
}

std::string ConfigBuilder::MakeAprString(const std::optional<network::ArpAddress>& arp_address){
    std::string res;
    if(arp_address.has_value()){
        res = detail::JoinWithSeparatorWiteSpace("ARP ADD"s,
                                                 boost::to_upper_copy(arp_address->ToString())
                                                 );
    }
    return res;
}

std::string ConfigBuilder::MakeAbonentRemoteString(const std::optional<abonent::AbonentRemote>& abonent){
    std::string res;
    if(abonent.has_value()){
        res = detail::JoinWithSeparatorWiteSpace("ABONENT ADD"s,
                                                 std::to_string(abonent->Number()),
                                                 abonent->Ip_addres(),
                                                 std::to_string(abonent->Mask().ShortRecord())
                                                 );
    }
    return res;
}

std::string ConfigBuilder::MakeTimetoliveString() const{
    std::string res;
    if(settings_.time.has_value()){
        std::string time = std::to_string(*settings_.time);
        res = detail::Join(" "s, "TIMETOLIVE"s, std::move(time));
    }
    return  res;
}

std::string ConfigBuilder::MakeProtocolString() const{
    std::string res;
    if(settings_.protocol.has_value()){
        std::string protocol =std::to_string(*settings_.protocol);
        res = detail::JoinWithSeparatorWiteSpace("PROTOCOL SET"s,std::move(protocol));
    }
    return  res;
}

} // namespace configurator
