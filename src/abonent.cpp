#include "abonent.h"
#include <sstream>

std::string Abonent::Address() const { return address_; }

int Abonent::Mask() const { return mask_; }

std::optional<int> Abonent::Devicenumber() const { return number_; }

std::string Abonent::ToString() const {

  std::stringstream str_stream;

  if (number_)
    str_stream << *number_<< " ";

  str_stream << address_ << " " << mask_;

  return str_stream.str();
}

AbonentType Abonent::AbonType() const { return abonent_type_; }
