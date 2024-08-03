#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <yaml-cpp/yaml.h>
#include "arp.h"
#include "abonent.h"
#include "IBuilder.h"
#include "abonent_remote.h"
#include "interface_settings.h"

namespace builder {

class FromYamlBuilder : public IBuilder
{
public:
    explicit FromYamlBuilder(std::istream& in): in_(in){};

    settings::Settings MakeSettings() override;

private:

    void Parse();
    InterfaceSettings GetInterfaceSettings(const YAML::Node& obj);
    abonent::Abonent GetInternalAbonent(const YAML::Node& obj);

    std::vector<abonent::AbonentRemote> GetAbonents(const YAML::Node& obj);
    std::vector<network::ArpAddress> GetArpAddresses(const YAML::Node& obj);

    YAML::Node document_;
    std::istream& in_;
};

}


