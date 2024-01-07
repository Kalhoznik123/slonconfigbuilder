#pragma once

#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>
#include <vector>
#include "IBuilder.h"
#include "interface_settings.h"
#include "abonent.h"
#include "abonent_remote.h"
#include "arp.h"

namespace builder {

class FromYamlBuilder : public IBuilder
{
public:
    FromYamlBuilder(const std::string& filename): filename_(filename){};

    settings::Settings MakeSettings() override;

private:

    void Parse();
    InterfaceSettings GetInterfaceSettings(const YAML::Node& obj);
    abonent::Abonent GetInternalAbonent(const YAML::Node& obj);

    std::vector<abonent::AbonentRemote> GetAbonents(const YAML::Node& obj);
    std::vector<network::ArpAddress> GetArpAddresses(const YAML::Node& obj);

    const std::string& filename_;
    YAML::Node document_;
};

}


