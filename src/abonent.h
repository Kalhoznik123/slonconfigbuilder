#pragma once
#include <optional>
#include <string>

class Abonent {

public:
  Abonent(const std::string& address, const std::string& mask,
          const std::optional<int>& number = std::nullopt)
      : address_(address), mask_(mask), number_(number) {}

private:
  std::string address_;
  std::string mask_;
  std::optional<int> number_;
};
