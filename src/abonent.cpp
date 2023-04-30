#include "abonent.h"
#include <sstream>

std::string Abonent::Address() const  noexcept{ return address_; }

int Abonent::Mask() const noexcept{ return mask_; }

std::optional<int> Abonent::Devicenumber() const noexcept{ return number_; }

std::string Abonent::ToString() const {

  std::stringstream str_stream;

  if (number_)
    str_stream << *number_<< " ";

  str_stream << address_ << " " << mask_;

  return str_stream.str();
}

AbonentType Abonent::AbonType() const noexcept{ return abonent_type_; }
