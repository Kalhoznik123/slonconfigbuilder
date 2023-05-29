#pragma once
#include "IBuilder.h"
#include "domain.h"
#include <iostream>

class Cin_builder : public IBuilder {

private:
  std::iostream& in_;

public:
  settings::Settings MakeSettings() override;
  Cin_builder(std::iostream& in) : in_(in){};
};