#pragma once
#include <string>
#include <string_view>

namespace network {

const std::string DELIMITERS = "[\\.,:-]";

class ARP {

public:
    explicit ARP(std::string_view mask);

    const std::string& Address() const;

private:
    std::string address_;

    bool IsValid(std::string_view mask) const;

    std::string Parse(std::string mask) const;

    template <typename Iterator>
    std::string Join(Iterator first, Iterator last) const {

        std::string result;
        for (; first != last; ++first) {
            result += *first;
        }
        return result;
    }

};

} // namespace network
