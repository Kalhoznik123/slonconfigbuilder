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
    /*!
@brief Возвращает значение внутреннего абонента.
@param Аргументов нет.
@return Возвращает класс описывающий внутреннего абонента.
*/
    abonent::Abonent MakeInternalAbonent();
    /*!
@brief Возвращает значение описывающие внутренний интерфейс.
@param Аргументов нет.
@return Возвращает класс описывающий внутренний интерфейс.
*/
    InterfaceSettings MakeLanSettings();
    /*!
@brief Возвращает значение описывающие внешнего интерфейса.
@param Аргументов нет.
@return Возвращает класс описывающий внешний интерфейс.
*/
    InterfaceSettings MakeInetSettings();
    /*!
@brief Возвращает вектор с удаленными абонентами.
@param Аргументов нет.
@return Возвращает вектор AbonentRemote.
*/
    std::vector<abonent::AbonentRemote> MakeRemoteAbonents();
    /*!
@brief Возвращает вектор ARP адрессов.
@param Аргументов нет.
@return Возвращает вектор ArpAddress.
*/
    std::vector<network::ArpAddress> MakeArpAddresses();
    /*!
@brief Возвращает значение времени.
@param Аргументов нет.
@return Возвращает значение времени в ввиде std::uint8_t.
*/
    std::uint8_t MakeTime();
    /*!
@brief Возвращает значенеи Devicenumber.
@param Аргументов нет.
@return Возвращает значенеи Devicenumber в виде int.
*/
    int MakeDevicenumber();
    /*!
@brief Возвращает значение protocol.
@param Аргументов нет.
@return Возвращает значение protocol в виде std::uint8_t.
*/
    std::uint8_t MakeProtocol();

public:
    settings::Settings MakeSettings() override;
    FromCinBuilder(std::istream& in) : in_(in){};
};
}
