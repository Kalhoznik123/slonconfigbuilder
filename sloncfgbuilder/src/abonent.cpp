#include <string>
#include <sstream>
#include "abonent.h"


namespace abonent{

std::string Abonent::Ip_addres() const noexcept { return addres_.Address(); }

const network::IP_Mask& Abonent::Mask() const noexcept { return mask_; }

}
