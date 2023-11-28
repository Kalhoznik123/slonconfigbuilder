#pragma once
#include "ARP.h"
#include "IBuilder.h"
#include "abonent.h"
#include "domain.h"
#include "interface_settings.h"
#include <iostream>
#include <vector>

class FromCinBuilder : public IBuilder {

private:
  std::istream& in_;

  Abonent MakeInternalAbonent();
  InterfaceSettings MakeLanSettings();
  InterfaceSettings MakeInetSettings();
  std::vector<AbonentRemote> MakeAbonents();
  std::vector<ArpAddress> MakeArpAddresses();
  std::uint8_t MakeTime();
  int MakeDevicenumber();
  std::uint8_t MakeProtocol();

public:
  settings::Settings MakeSettings() override;
  FromCinBuilder(std::istream& in) : in_(in){};
};
