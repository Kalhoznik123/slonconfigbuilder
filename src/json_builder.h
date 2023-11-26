#pragma once
#include "IBuilder.h"
#include "config_builder.h"
#include "domain.h"
#include <functional>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
class FromJsonBuilder : public IBuilder {

public:
    using json = nlohmann::json;

    FromJsonBuilder(std::istream& in)
        : in_(in){};

    settings::Settings MakeSettings() override;

private:
    void Parse();
    static std::vector<Abonent> GetAbonents(const json& obj);
    static std::vector<ArpAddress> GetArpAddresses(const json& obj);
    static InterfaceSettings GetInterfaceSettings(const json& obj);
    static Abonent GetInternalAbonent(const json& obj);
    json document_;
    std::istream& in_;

};
