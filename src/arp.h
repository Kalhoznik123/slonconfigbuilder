#pragma once
/*!
\file
\brief Заголовочный файл с описывающий ARP адрес.
*/
#include <string>
#include <string_view>
#include "ARP.h"

namespace network {
/*!
@brief Класс, описывающий ARP адрес .
@todo избавиться от метода ToString
Класс описывает ARP адресс который вводится коммандой ARP ADD.
*/
class ArpAddress {

public:

    ArpAddress(std::uint8_t number, std::string_view arp_address)
        : number_(number), arp_address_(network::ARP(arp_address)) {}
    /*!
@brief Возвращает значение ARP адресса.
@param Аргументов нет.
@return Возвращает строку со значением ARP адресса.
*/
    std::string Address() const noexcept;
    /*!
@brief Возвращает значение порядковый номер ARP адресса.
@param Аргументов нет.
@return Возвращает порядкоывый номер ARP адресса.
*/
    int Number() const noexcept;
    std::string ToString() const;

private:
    int number_;
    network::ARP arp_address_;
};
}
