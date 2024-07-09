#pragma once
/*!
\file
\brief Заголовочный файл описывает структуру конфигурационного фалайла
и функции для склейки строк.
*/
#include "abonent.h"
#include "abonent_remote.h"
#include "arp.h"
#include "interface_settings.h"
#include <optional>
#include <vector>

namespace settings {
/*!
    @brief Структура описывающая  конфигурационный файл.
*/
struct Settings {
  std::optional<abonent::Abonent> internal_abonent_;
  std::optional<InterfaceSettings> lan_settings;
  std::optional<InterfaceSettings> inet_settings;
  std::optional<std::vector<abonent::AbonentRemote>> abonents_;
  std::optional<std::vector<network::ArpAddress>> arp_addresses_;
  std::optional<std::uint8_t> time;
  std::optional<int> devicenumber;
  std::optional<std::uint8_t> protocol;
};
} // namespace settings

namespace detail {

// template<typename T>
// auto Join(const std::string& separator, const T& first)->decltype (first){
//     return first;
// }

template <typename T>
auto Join(const std::string &separator, T &&first) -> decltype(first) {
  return std::forward<T>(first);
}

template <typename T, typename... Tail>
auto Join(const std::string &separator, T &&first,
          Tail &&...tail) -> decltype(first + separator) {
  if (std::forward<T>(first).empty()) {
    return Join(separator, std::forward<Tail>(tail)...);
  }
  return first + separator + Join(separator, tail...);
}

template <typename... Args>
decltype(auto) JoinWithSeparatorWiteSpace(Args &&...args) {
  return Join(std::string(" "), std::forward<Args>(args)...);
}
} // namespace detail
