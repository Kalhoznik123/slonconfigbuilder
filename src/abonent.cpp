#include "abonent.h"

std::string Abonent::Address() const { return address_; }

int Abonent::Mask() const { return mask_; }

std::optional<int> Abonent::Devicenumber() const { return number_; }

std::string Abonent::ToString() const { 
  //TODO: добавить реализауию
  
  return std::string(); }
