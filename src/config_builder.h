#pragma once
#include "abonent.h"
#include "arp.h"
#include "domain.h"
#include <optional>
#include <vector>

namespace configurator {

class ConfigBuilder {
public:
  ConfigBuilder() = default;
  ConfigBuilder(const settings::Settings& settings)
      : settings_(settings){

        };

  std::string Dump() const;

private:
// FuncObj функциональный объект который принимает Container::value_type value
  template<typename Container, typename FuncObj>
  static std::string CommonObjContainerStringMaker(const Container& container, FuncObj MakeString) {
      bool is_first = true;
      std::string res;

      for (const auto& abonent : container) {

          if (is_first) {
              res.append(MakeString(abonent));
              is_first = false;
              continue;
          }
          res.append("\n").append(MakeString(abonent));
      }
      return  res;
  }


  static std::string MakeAbonentString(const Abonent& abonent);
  static std::string MakeAprString(const ArpAddress& arp_address);
  static std::string MakeInterfaceString(const InterfaceSettings& settings);
  static std::string MakeAbonentRemoteString(const AbonentRemote& abonent);
  static std::string MakeAbonentsString(const std::vector<AbonentRemote>& abonents) ;
  std::string MakeDevicenumber() const;
  std::string MakeTimetoliveString() const;
  std::string MakeProtocolString() const;
  std::string MakeArpAddressesString(const std::vector<ArpAddress>& arp_adresses) const;

private:
  settings::Settings settings_;
};

} // namespace configurator
