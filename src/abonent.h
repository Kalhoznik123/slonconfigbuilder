#pragma once
#include <optional>
#include <string>

class Abonent {

public:
  Abonent() = default;

  Abonent(const std::string& address, int mask,
          const std::optional<int>& number = std::nullopt)
      : address_(address), mask_(mask), number_(number) {}

std::string GetAddress();


private:
  std::string address_;
  int mask_;
  std::optional<int> number_;
};
