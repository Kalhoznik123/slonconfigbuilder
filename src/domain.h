#pragma once
#include "abonent.h"
#include "arp.h"
#include "interface_settings.h"
#include "abonent_remote.h"
#include <optional>
#include <vector>
namespace settings {

struct Settings {

  Abonent internal_abonent_;
  InterfaceSettings lan_settings;
  InterfaceSettings inet_settings;
  std::vector<AbonentRemote> abonents_;
  std::vector<ArpAddress> arp_addresses_;
  std::optional<std::uint8_t> time;
  std::optional<int> devicenumber;
  std::optional<std::uint8_t> protocol;
};
} // namespace settings

namespace detail {


template<typename T>
auto join(const std::string& separator, const T& first)->decltype (first){
    return first;
}


template<typename T,typename... Tail>
auto join(const std::string& separator,const T& first, const Tail&... tail)->decltype (first + separator ){
    return first + separator +join(separator, tail...) ;
}

template<typename... Args>
decltype (auto) JoinWithSeparatorWiteSpace(const Args&... args){
    return join(std::string(" "),args...);
}
}
