#include "abonent.h"
#include <sstream>
#include <string>
const std::string& Abonent::Address() const noexcept { return address_; }

std::variant<int,std::string> Abonent::Mask() const noexcept { return mask_; }

const std::optional<int>& Abonent::Devicenumber() const noexcept {
  return number_;
}

std::string Abonent::ToString() const {

  std::stringstream str_stream;

  if (number_)
    str_stream << *number_ << " ";

  str_stream << address_ << " " ;

  std::visit([&str_stream](const auto& obj) { str_stream << obj; }, mask_);

  return str_stream.str();
}

const AbonentType& Abonent::AbonType() const noexcept { return abonent_type_; }
