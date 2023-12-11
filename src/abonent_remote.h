#pragma  once
/*!
\file
\brief Заголовочный файл с описывающий удаленного абонента.
*/

#include <optional>
#include <string>
#include <variant>
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
                  const network::IP_Mask& mask, std::uint8_t number):
        Abonent(std::string(address),mask),number_(number) {};
    /*!
  @brief Возвращает значение порядквого номера абонента
  @param Аргументов нет.
  @return Возвращает порядковый номер абонента.
  */
 std::uint8_t Number()const noexcept;

private:
    std::uint8_t number_{0};
};


}
