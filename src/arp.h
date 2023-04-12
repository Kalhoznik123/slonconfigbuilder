#pragma once
#include <string>

class ArpAdress {

public:
  ArpAdress(std::uint8_t number, const std::string& address)
      : number_(number), address_(address) {}

private:
  std::uint8_t number_;
  std::string address_;
};