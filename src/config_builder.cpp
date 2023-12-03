#include <boost/algorithm/string.hpp>
#include <sstream>
#include <string>
#include "config_builder.h"
#include "abonent_remote.h"
#include "domain.h"

namespace configurator {

std::string ConfigBuilder::Dump() const {
    const std::string update_command = "UPDATE\n";

    auto res = detail::join(std::string("\n"),
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
    const std::string res = detail::join(std::string(" "),
                                         std::string("DEVICENUMBER"),
                                         std::to_string(*settings_.devicenumber));
    return  res;
}
std::string ConfigBuilder::MakeAbonentString(const Abonent& abonent) {

    const std::string res = detail::JoinWithSeparatorWiteSpace(std::string("ABONENT ADD INTERNAL"),
                                                               abonent.Address(),
                                                               std::to_string(abonent.Mask().ShortRecord())
                                                               );
    return  res;
}

std::string ConfigBuilder::MakeAprString(const ArpAddress& arp_address){
    const std::string res = detail::JoinWithSeparatorWiteSpace(std::string("ARP ADD"),
                                                               boost::to_upper_copy(arp_address.ToString())
                                                               );
    return res;
}

std::string ConfigBuilder::MakeInterfaceString(const InterfaceSettings& iterface_settings){
    std::string interface_type = iterface_settings.interface_type == InterfaceType::LAN ? "LAN" : "INET";
    const auto res = detail::join(std::string(" "),std::string("IFCONFIG"),
                                  std::move(interface_type),
                                  std::to_string(iterface_settings.speed) + iterface_settings.mode
                                  );
    return  res;
}

std::string ConfigBuilder::MakeAbonentRemoteString(const AbonentRemote& abonent){
    return detail::JoinWithSeparatorWiteSpace(std::string("ABONENT ADD"),
                                              std::to_string(abonent.Number()),
                                              abonent.Address(),
                                              std::to_string(abonent.Mask().ShortRecord())
                                              );
}

std::string ConfigBuilder::MakeTimetoliveString() const{
    std::string time = settings_.time ? std::to_string(*settings_.time) : "80";
    const auto res = detail::join(std::string(" "), std::string("TIMETOLIVE"), std::move(time));
    return  res;
}

std::string ConfigBuilder::MakeProtocolString() const{
    std::string protocol =settings_.protocol ? std::to_string(*settings_.protocol) : "53";
    return  detail::JoinWithSeparatorWiteSpace(std::string("PROTOCOL"),std::move(protocol));
}

std::string ConfigBuilder::MakeAbonentsString(const std::vector<AbonentRemote>& abonents){
    const auto res = CommonObjContainerStringMaker(abonents,&MakeAbonentRemoteString);
    return res;
}

std::string ConfigBuilder::MakeArpAddressesString(const std::vector<ArpAddress>& arp_adresses) const{
    const auto res = CommonObjContainerStringMaker(arp_adresses,&MakeAprString);
    return res;
}
} // namespace configurator
