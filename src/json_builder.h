#pragma once
/*!
\file
\brief Заголовочный файл для класса считывателя json.
*/
#include <functional>
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
#include "IBuilder.h"
#include "config_builder.h"
#include "domain.h"
#include "abonent_remote.h"

namespace builder{
/*!
    @brief Класс для чтения json файла.
*/
class FromJsonBuilder : public IBuilder {

public:
    using json = nlohmann::json;

    FromJsonBuilder(std::istream& in)
        : in_(in){};
    /*!
@brief Функция для построения структуры  описывающей файл конфигурацию.
@return Возвращает значение структуры описывающей файл конфигурацию.
*/
    settings::Settings MakeSettings() override;

private:
    void Parse();
    static std::vector<abonent::AbonentRemote> GetAbonents(const json& obj);
    static std::vector<network::ArpAddress> GetArpAddresses(const json& obj);
    static InterfaceSettings GetInterfaceSettings(const json& obj);
    static abonent::Abonent GetInternalAbonent(const json& obj);
    json document_;
    std::istream& in_;
};
}
