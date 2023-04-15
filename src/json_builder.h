
#pragma once
#include "config_builder.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include "domain.h"

class JsonBuilder {
public:
 using json = nlohmann::json; 
  
  JsonBuilder(std::istream& in=std::cin):in_(in){

  };

settings::Settings MakeSettings();


private:


  void Parse();

json document_;
std::istream& in_;
};