#include "abonent_remote.h"

namespace abonent{
uint8_t AbonentRemote::Number() const noexcept{
    return  number_;
}

const std::optional<std::string> &AbonentRemote::Description() const{
    return  description_;
}
}
