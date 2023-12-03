#pragma once
#include <optional>
#include <string>
#include <variant>
#include "ip_mask.h"





class Abonent  {

public:
  Abonent() = default;

  Abonent(const std::string& address,
          const IP_Mask& mask )
      : address_(address), mask_(mask){}

  const std::string& Address() const noexcept;
  const IP_Mask& Mask() const noexcept;  
  std::string ToString() const;  

private:
  std::string address_;
  IP_Mask mask_;
};


