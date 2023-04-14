
#pragma once
#include "config_builder.h"
#include <iostream>

class JsonBuilder {
public:
  JsonBuilder(ConfigBuilder& config)
      : config_(config){

        };

void Parse(std::istream& in);



private:
  ConfigBuilder& config_;
};