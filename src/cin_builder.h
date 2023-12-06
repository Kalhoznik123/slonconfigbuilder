#pragma once
/*!
\file
\brief Заголовочный файл с описывающий класс для чтения данных из стандартного потока.
*/
#include <iostream>
#include <vector>
#include "ARP.h"
#include "IBuilder.h"
#include "abonent.h"
#include "domain.h"
#include "interface_settings.h"

namespace builder{
/*!
    @brief Класс для получения данных из стандартного потока и создания структуры с конфигуацией .

    Класс читает стандартный вход и создает настроки структуру с конфигурацией.
*/
class FromCinBuilder : public IBuilder {

private:
    std::istream& in_;

    abonent::Abonent MakeInternalAbonent();
    InterfaceSettings MakeLanSettings();
    InterfaceSettings MakeInetSettings();
    std::vector<abonent::AbonentRemote> MakeAbonents();
    std::vector<network::ArpAddress> MakeArpAddresses();
    std::uint8_t MakeTime();
    int MakeDevicenumber();
    std::uint8_t MakeProtocol();

public:
    settings::Settings MakeSettings() override;
    FromCinBuilder(std::istream& in) : in_(in){};
};
}
