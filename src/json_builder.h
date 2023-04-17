
#pragma once
#include "config_builder.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include "domain.h"
#include <vector>


class JsonBuilder {
public:
 using json = nlohmann::json; 
  
  JsonBuilder(std::istream& in=std::cin):in_(in){

  };

settings::Settings MakeSettings();


private:


  void Parse();
  std::vector<Abonent> GetAbonents(const json& obj);
  std::vector<ArpAddress> GetArpAddresses(const json& obj);


json document_;
std::istream& in_;
};