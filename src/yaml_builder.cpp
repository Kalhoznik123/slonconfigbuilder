#include "yaml_builder.h"
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <optional>

#undef YAML_CPP_NOEXCEPT
std::optional<int> TryConvert(const std::string value){
    int val = 0;
    const bool OK =boost::conversion::try_lexical_convert(value,val);
    std::optional<int> res;

    if(OK)
        res = val;

    return  res;
}

namespace builder {

settings::Settings FromYamlBuilder::MakeSettings()
{

    settings::Settings settings;

    if(document_.IsNull())
        Parse();

    if(const auto protocol_val =document_["protocol"];protocol_val.IsDefined() ){
        settings.protocol = protocol_val.as<std::uint8_t>();
    }
    if(const auto time_val = document_["time"];time_val.IsDefined() ){
        settings.time = time_val.as<std::uint8_t>();
    }
    if(const auto devicenumber_val = document_["devicenumber"];devicenumber_val.IsDefined() ){
        settings.devicenumber = devicenumber_val.as<int>();
    }
    if(const auto inet_val = document_["inet"];inet_val.IsDefined() ){
        settings.inet_settings = GetInterfaceSettings(inet_val);
    }
    if(const auto lan_val = document_["lan"];lan_val.IsDefined()){
        settings.lan_settings = GetInterfaceSettings(lan_val);
    }
    if(const auto internal_val = document_["internal"];internal_val.IsDefined()){
        settings.internal_abonent_ = GetInternalAbonent(internal_val);
    }
    if(const auto abonents_val = document_["abonents"];abonents_val.IsDefined()){
        settings.abonents_ = GetAbonents(abonents_val);
    }
    if(const auto arp_val = document_["arp"];arp_val.IsDefined()){
        settings.arp_addresses_ = GetArpAddresses(arp_val);
    }
    return  settings;
}

void FromYamlBuilder::Parse()
{
    try{
      document_ = YAML::Load(in_);

    }  catch (std::exception& e) {
        using namespace std::string_literals;

        std::cout <<e.what() << '-' << boost::to_upper_copy("bad yaml parse\n"s);
    }
}

InterfaceSettings FromYamlBuilder::GetInterfaceSettings(const YAML::Node &obj) {

    InterfaceType type = obj["type"].as<std::string>() == "LAN"
            ? InterfaceType::LAN
            : InterfaceType::INET;

    return {obj["speed"].as<int>(), obj["mode"].as<std::string>(), type};
}

abonent::Abonent FromYamlBuilder::GetInternalAbonent(const YAML::Node &obj) {
    network::IP_Mask mask;

    try{
        mask.Mask(obj["mask"].as<std::string>());
    }catch(...){
        mask.Mask(obj["mask"].as<int>());
    }

    abonent::Abonent abonent(obj["address"].as<std::string>(), mask);

    return abonent;
}

std::vector<abonent::AbonentRemote> FromYamlBuilder::GetAbonents(const YAML::Node& obj) {

    std::vector<abonent::AbonentRemote> abonents;
    abonents.reserve(obj.size());

    for (const auto& abonent_node : obj) {
        network::IP_Mask mask;


        try{
            mask.Mask(abonent_node["mask"].as<std::string>());
        }catch(... ){
            mask.Mask(abonent_node["mask"].as<int>());
        }

        abonents.emplace_back(abonent_node["address"].as<std::string>(),
                mask, abonent_node["number"].as<int>());
    }
    return abonents;
}

std::vector<network::ArpAddress> FromYamlBuilder::GetArpAddresses(const YAML::Node &obj) {

    std::vector<network::ArpAddress> arp_addresses;
    arp_addresses.reserve(obj.size());

    for (const auto& arp_node : obj) {

        arp_addresses.emplace_back(arp_node["number"].as<int>(),arp_node["arp_address"].as<std::string>());

    }
    return arp_addresses;
}

}
