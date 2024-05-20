#pragma  once
/*!
\file
\brief Заголовочный файл с описывающий удаленного абонента.
*/

#include <optional>
#include <string>
#include <string_view>
#include "ip_mask.h"
#include "abonent.h"

namespace abonent{
/*!
    @brief Класс, описывающий удаленного абонента .

    Класс описывает удаленного абонента который вводится коммандой ABONENT ADD.
*/
class AbonentRemote : public Abonent
{
public:
    AbonentRemote(std::string_view address,
                  const network::IP_Mask& mask, std::uint8_t number, const std::optional<std::string>& description = std::nullopt):
        Abonent(std::string(address),mask),number_(number),description_(description) {};
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
    const std::optional<std::string>& Description() const ;
private:
    std::uint8_t number_{0};
    std::optional<std::string> description_;
};


}
