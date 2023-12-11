
#pragma once
/*!
\file
\brief Заголовочный файл с описывающий внутреннего абонента.
*/
#include <optional>
#include <string>
#include <variant>
#include <string_view>
#include "ip_mask.h"

namespace abonent{
/*!
    @brief Класс, описывающий внитреннего абонета.

    Класс описывает внутреннего абонента который вводим командой internal.
*/
class Abonent  {

public:
    Abonent() = default;

    Abonent(std::string_view address,
            const network::IP_Mask& mask )
        : address_(std::string(address)), mask_(mask){}

    /*!
  @brief Возвращает значение IP адресса.
  @param Аргументов нет.
  @return Возвращает строку с IP адрессом.
  */
    const std::string& Address() const noexcept;
    /*!
  @brief Возвращает значение маски подсети
  @param Аргументов нет.
  @return Возвращает класс описыващий маску подсети
  */
    const network::IP_Mask& Mask() const noexcept;


private:
    std::string address_;
    network::IP_Mask mask_;
};


}
