#pragma once
/*!
\file
\brief Заголовочный файл описывает маску подсети.
*/
#include <bitset>
#include <cstdint>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace network {

const std::uint8_t MAX_MASK_VALUE =
    32; ///< Переменная для указания максимальной длинны мыски подсети.
/*!
    @brief Класс описывает маску подсети
*/
class IP_Mask {
public:
  IP_Mask() = default;
  IP_Mask(const IP_Mask &other)
      : bits(other.bits), string_form_(other.string_form_){};
  IP_Mask(IP_Mask &&rhs) noexcept
      : bits(std::move(rhs.bits)), string_form_(std::move(rhs.string_form_)){};
  IP_Mask &operator=(const IP_Mask &rhs) {
    bits = rhs.bits;
    string_form_ = rhs.string_form_;
    return *this;
  }

  IP_Mask &operator=(IP_Mask &&rhs) noexcept {
    bits = std::move(rhs.bits);
    string_form_ = std::move(rhs.string_form_);
    return *this;
  }
  ~IP_Mask() = default;

  explicit IP_Mask(uint8_t var);
  ;
  explicit IP_Mask(std::string_view var);
  ;

  /*!
@brief Функция устанавливает значение маски.
@param value - значение маски в виде числа.
*/
  void Mask(std::uint8_t value);
  /*!
@brief Функция устанавливает значение маски.
@param value - значение маски в виде строки.
*/
  void Mask(std::string_view value);
  /*!
@brief Функция вычисляет значение маски подсети в виде числа.
@return Возвращает число, как значение маски.
*/
  std::size_t ShortRecord() const noexcept;
  /*!
@brief Функция вычисляет значение маски подсети в виде строки.
@return Возвращает число, как значение строки.
*/
  std::string FullRecord() const noexcept;
  /*!
@brief Функция сравнение на меньше.
@return Возвращает результат стравнения.
*/
  bool operator<(const IP_Mask &other) const;
  /*!
@brief Функция не равно.
@return Возвращает результат стравнения.
*/
  bool operator!=(const IP_Mask &other) const;
  /*!
@brief Функция сравнение на больше.
@return Возвращает результат стравнения.
*/
  bool operator>(const IP_Mask &other) const;
  /*!
@brief Функция сравнение на равно.
@return Возвращает результат стравнения.
*/
  bool operator==(const IP_Mask &other) const;

private:
  using bit32_t = std::bitset<MAX_MASK_VALUE>;

  template <typename BitContainer> size_t countl_one(BitContainer value) {

    size_t res{0};
    for (int i = value.size() - 1; i >= 0; --i) {
      if (!value[i])
        break;
      ++res;
    }
    return res;
  }

  template <typename T> // передается по значению потому что используется только
                        // для string_view и uint8_t
                        void ValidationCheck(T var) {
    if constexpr (std::is_same_v<T, std::uint8_t>) {
      NumValidation(var);
    } else {
      StringValidation(var);
    }
  }

  std::string StringFromBits() const;

  std::size_t GetOctet(std::size_t number_of_octet) const;
  void NumValidation(std::uint8_t var);
  void StringValidation(std::string_view var);

  static std::vector<std::uint8_t>
  StringsToNums(std::vector<std::string> strings);
  static bit32_t BitsFromNums(std::vector<std::uint8_t> nums);
  static bit32_t BitsFromMask(std::string_view mask);

private:
  static const std::uint8_t MAX_MASK_LENGTH = 24;
  static const std::uint8_t OCTET_LENGTH = 8;
  bit32_t bits;
  mutable std::optional<std::string> string_form_;
};

} // namespace network
