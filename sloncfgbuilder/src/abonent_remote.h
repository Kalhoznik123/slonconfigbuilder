#pragma once
/*!
\file
\brief Заголовочный файл с описывающий удаленного абонента.
*/

#include "abonent.h"
#include "ip_mask.h"
#include <optional>
#include <string>
#include <string_view>

namespace abonent {
/*!
    @brief Класс, описывающий удаленного абонента .

    Класс описывает удаленного абонента который вводится коммандой ABONENT ADD.
*/
class AbonentRemote : public Abonent {
public:
  AbonentRemote(std::string_view address, network::IP_Mask mask,
                std::uint8_t number, std::optional<std::string> description)
      : Abonent(std::string(address), std::move(mask)), number_(number),
        description_(std::move(description)){};

  AbonentRemote(std::string_view address, const network::IP_Mask &mask,
                std::uint8_t number)
      : Abonent(std::string(address), mask), number_(number){};
  /*!
@brief Возвращает значение порядквого номера абонента
@param Аргументов нет.
@return Возвращает порядковый номер абонента.
*/
  std::uint8_t Number() const noexcept;
  /*!
@brief Возвращает значение описания
@param Аргументов нет.
@return Возвращает порядковый optional от описания.
*/
  const std::optional<std::string> &Description() const;

private:
  std::uint8_t number_{0};
  std::optional<std::string> description_ = std::nullopt;
};

} // namespace abonent
