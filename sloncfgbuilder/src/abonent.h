
#pragma once
/*!
\file
\brief Заголовочный файл с описывающий внутреннего абонента.
*/
#include "ip_address.h"
#include "ip_mask.h"
#include <optional>
#include <string>
#include <string_view>
#include <variant>

namespace abonent {
/*!
    @brief Класс, описывающий внитреннего абонета.

    Класс описывает внутреннего абонента который вводим командой internal.
*/
class Abonent {

public:
  Abonent(std::string_view address, network::IP_Mask mask)
      : addres_(std::string(address)), mask_(std::move(mask)) {}

  Abonent(const Abonent &other) : addres_(other.addres_), mask_(other.mask_) {}
  Abonent(Abonent &&other) noexcept
      : addres_(std::move(other.addres_)), mask_(std::move(other.mask_)) {}
  Abonent &operator=(const Abonent &rhs) {
    addres_ = rhs.addres_;
    mask_ = rhs.mask_;
    return *this;
  }
  Abonent &operator=(Abonent &&rhs) noexcept {
    addres_ = std::move(rhs.addres_);
    mask_ = std::move(rhs.mask_);
    return *this;
  }
  virtual ~Abonent()= default;
  /*!
@brief Возвращает значение IP адресса.
@param Аргументов нет.
@return Возвращает строку с IP адрессом.
*/
  std::string Ip_addres() const noexcept;
  /*!
@brief Возвращает значение маски подсети
@param Аргументов нет.
@return Возвращает класс описыващий маску подсети
*/
  const network::IP_Mask &Mask() const noexcept;

private:
  IP_addres addres_;
  network::IP_Mask mask_;
};

} // namespace abonent
