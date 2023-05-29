#pragma once
#include "domain.h"

class IBuilder {

public:
  virtual ~IBuilder(){

  };

  virtual settings::Settings MakeSettings() = 0;
};
