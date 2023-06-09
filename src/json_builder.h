
#pragma once
#include "config_builder.h"
#include "domain.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>

class JsonBuilder {
public:
  using json = nlohmann::json;

  JsonBuilder(std::istream& in = std::cin)
      : in_(in){

        };

  settings::Settings MakeSettings();

private:
  void Parse();
  static std::vector<Abonent> GetAbonents(const json& obj);
  static std::vector<ArpAddress> GetArpAddresses(const json& obj);
  static InterfaceSettings GetInterfaceSettings(const json& obj);
  static Abonent GetInternalAbonent(const json& obj);
  json document_;
  std::istream& in_;
};