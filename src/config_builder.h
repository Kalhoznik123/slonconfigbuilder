#pragma once
/*!
\file
\brief Заголовочный файл с описывающий класс ConfigBuilder для создания конфигурацции.
*/
#include <optional>
#include <vector>
#include "abonent.h"
#include "arp.h"
#include "domain.h"

namespace configurator {
/*!
    @brief Класс который формирует строку конфигурации.
*/
class ConfigBuilder {
public:
  ConfigBuilder() = default;
  ConfigBuilder(const settings::Settings& settings)
      : settings_(settings){

        };

  std::string Dump() const;

private:
  /*!
@brief Создает из контейнера обектов стоку в соответтвии с функцией(FuncObj) создателем строк.
@param FuncObj функциональный объект который принимает Container::value_type value.
@param Container с обектами из которых нужно создвать строки.
@return Строка с состоящая из обектов Container::value_type приобразованных в строки при помщи FuncObj.
*/

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


  static std::string MakeAbonentString(const abonent::Abonent& abonent);
  static std::string MakeAprString(const network::ArpAddress& arp_address);
  static std::string MakeInterfaceString(const InterfaceSettings& settings);
  static std::string MakeAbonentRemoteString(const abonent::AbonentRemote& abonent);
  static std::string MakeAbonentsString(const std::vector<abonent::AbonentRemote>& abonents) ;
  std::string MakeDevicenumber() const;
  std::string MakeTimetoliveString() const;
  std::string MakeProtocolString() const;
  std::string MakeArpAddressesString(const std::vector<network::ArpAddress>& arp_adresses) const;

private:
  settings::Settings settings_;
};

} // namespace configurator
