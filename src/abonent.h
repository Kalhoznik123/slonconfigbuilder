#pragma once
#include <optional>
#include <string>
#include <variant>
#include "ip_mask.h"

enum class AbonentType { INTERNAL, REMOTE };

class Abonent {

public:
  Abonent() = default;

  Abonent(const std::string& address,
          const IP_Mask& mask, AbonentType abonent_type,
          const std::optional<int>& number = std::nullopt)
      : address_(address), mask_(mask), abonent_type_(abonent_type),
        number_(number) {}

  const std::string& Address() const noexcept;
  const IP_Mask& Mask() const noexcept;
  const std::optional<int>& Devicenumber() const noexcept;
  std::string ToString() const;
  const AbonentType& AbonType() const noexcept;

private:
  std::string address_;
  IP_Mask mask_;
  //std::variant<int, std::string> mask_;
  AbonentType abonent_type_;
  std::optional<int> number_;
};
