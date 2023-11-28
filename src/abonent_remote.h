#pragma  once
#include <optional>
#include <string>
#include <variant>
#include "ip_mask.h"
#include "abonent.h"

class AbonentRemote : public Abonent
{
public:
    AbonentRemote(const std::string& address,
                  const IP_Mask& mask, std::uint8_t number):
        Abonent(address,mask),number_(number) {};

 std::uint8_t Number()const noexcept;

private:
    std::uint8_t number_{0};
};


