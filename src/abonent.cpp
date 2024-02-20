#include <sstream>
#include <string>
#include "abonent.h"


namespace abonent{
const std::string& Abonent::Address() const noexcept { return address_; }

const network::IP_Mask& Abonent::Mask() const noexcept { return mask_; }

}
