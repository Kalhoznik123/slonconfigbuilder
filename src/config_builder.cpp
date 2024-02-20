#include <boost/algorithm/string.hpp>
#include <sstream>
#include <string>
#include "config_builder.h"
#include "abonent_remote.h"
#include "domain.h"

namespace configurator {

std::string ConfigBuilder::Dump() const {

    const std::string update_command = "UPDATE\n";

    auto res = detail::Join(std::string("\n"),
                            MakeDevicenumber(),
                            MakeAbonentString(settings_.internal_abonent_),
                            MakeAbonentsString(settings_.abonents_),
                            MakeArpAddressesString(settings_.arp_addresses_),
                            MakeInterfaceString(settings_.lan_settings),
                            MakeInterfaceString(settings_.inet_settings),
                            MakeTimetoliveString(),
                            MakeProtocolString(),
                            update_command
                            );


    return res;
}

std::string ConfigBuilder::MakeDevicenumber() const {

    std::string res;

    if(settings_.devicenumber.has_value()){
        res = detail::Join(std::string(" "),std::string("DEVICENUMBER"),
                           std::to_string(*settings_.devicenumber));
    }

    return  res;
}

std::string ConfigBuilder::MakeAbonentString(const std::optional<abonent::Abonent>& abonent) {

    std::string res;
    if(abonent.has_value()){
        res = detail::JoinWithSeparatorWiteSpace(std::string("ABONENT ADD INTERNAL"),
                                                 abonent->Address(),
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
        std::string interface_type = interface_settings->interface_type == InterfaceType::LAN ? "LAN" : "INET";
        res = detail::Join(std::string(" "),std::string("IFCONFIG"),
                           std::move(interface_type),
                           std::to_string(interface_settings->speed) + interface_settings->mode
                           );

    }
    return  res;
}

std::string ConfigBuilder::MakeAprString(const std::optional<network::ArpAddress>& arp_address){

    std::string res;
    if(arp_address.has_value()){
        res = detail::JoinWithSeparatorWiteSpace(std::string("ARP ADD"),
                                                 boost::to_upper_copy(arp_address->ToString())
                                                 );
    }
    return res;
}

std::string ConfigBuilder::MakeAbonentRemoteString(const std::optional<abonent::AbonentRemote>& abonent){

    std::string res;
    if(abonent.has_value()){
        res = detail::JoinWithSeparatorWiteSpace(std::string("ABONENT ADD"),
                                                 std::to_string(abonent->Number()),
                                                 abonent->Address(),
                                                 std::to_string(abonent->Mask().ShortRecord())
                                                 );
    }

    return res;
}

std::string ConfigBuilder::MakeTimetoliveString() const{

    std::string res;
    if(settings_.time.has_value()){
        std::string time = std::to_string(*settings_.time);
        res = detail::Join(std::string(" "), std::string("TIMETOLIVE"), std::move(time));
    }

    return  res;
}

std::string ConfigBuilder::MakeProtocolString() const{

    std::string res;
    if(settings_.protocol.has_value()){
        std::string protocol =std::to_string(*settings_.protocol);
        detail::JoinWithSeparatorWiteSpace(std::string("PROTOCOL"),std::move(protocol));
    }

    return  res;
}


} // namespace configurator
