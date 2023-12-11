#include "ARP.h"
#include <exception>
#include <regex>

namespace network {

// "01-23-45-67-89-AB";
// "01:23:45:67:89:AB";
// "0123.4567.89AB";
/*
сверху обявлены форматы записи мак адресов

*/
ARP::ARP(std::string_view mask) {

  if (IsValid(mask)) {
    address_ = Parse(std::string(mask));

  } else {
    throw std::invalid_argument("invalid ip mask");
  }
}

bool ARP::IsValid(std::string_view mask) const {

  const std::regex pattern("^([0-9A-Fa-f]{2}[:-]){5}"
                           "([0-9A-Fa-f]{2})|([0-9a-"
                           "fA-F]{4}\\.[0-9a-fA-F]"
                           "{4}\\.[0-9a-fA-F]{4})|([0-9A-Fa-f]{12})$");

  // Return true if the MAC address
  // matched the ReGex
  return std::regex_match(std::string(mask), pattern);
}

const std::string& ARP::Address() const { return address_; }

std::string ARP::Parse(std::string mask) const {

  const std::regex re(DELIMITERS);

  std::sregex_token_iterator first{mask.cbegin(), mask.cend(), re, -1},
      last; // the '-1' is what makes the regex split (-1 := what was not
            // matched)
  std::vector<std::string> tokens{first, last};

  const std::string result = Join(first, last);

  return result;
}
} // namespace network
