#include "abonent.h"
#include <sstream>
#include <string>

const std::string& Abonent::Address() const noexcept { return address_; }

const IP_Mask& Abonent::Mask() const noexcept { return mask_; }


std::string Abonent::ToString() const {

    std::stringstream str_stream;

    str_stream << address_ << " " ;

    str_stream << std::to_string(mask_.ShortRecord());

    return str_stream.str();
}


