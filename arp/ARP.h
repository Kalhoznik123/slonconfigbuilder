#pragma once
#include <string>



namespace network {

class ARP {

public:
  explicit ARP(const std::string& mask);

 const std::string& ToString() const;

private:
  std::string address_;
  bool IsValid(const std::string& mask) const;

  std::string Parse(const std::string& mask) const;

  template <typename Iterator>
  std::string Join(Iterator first, Iterator last) const {

    std::string result;

    for (; first != last; ++first) {
      result += *first;
    }

    return result;
  }

  const std::string DELIMITERS = "[\\.,:-]";
};

} // namespace network
