#pragma once
#include "abonent.h"
#include "arp.h"
#include "domain.h"
#include <optional>
#include <vector>

class ConfigBuilder {
public:
  ConfigBuilder();
  ConfigBuilder(const settings::Settings& settings)
      : settings_(settings){

        };

std::string Dump();


private:
  
  
  
  settings::Settings settings_;
};