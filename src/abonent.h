#pragma once
#include <optional>
#include <string>

enum class AbonentType {
  INTERNAL,
  REMOTE
};

class Abonent {

public:
  Abonent() = default;

  Abonent(const std::string& address, int mask, AbonentType abonent_type,
          const std::optional<int>& number = std::nullopt)
      : address_(address), mask_(mask), abonent_type_(abonent_type),
        number_(number) {}

  std::string Address() const;

  int Mask() const;

  std::optional<int> Devicenumber() const;
  std::string ToString() const;
  AbonentType AbonType() const;

private:
  std::string address_;
  int mask_;
  AbonentType abonent_type_;
  std::optional<int> number_;
};