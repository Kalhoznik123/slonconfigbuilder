#pragma once

#include <optional>
#include <bitset>
#include <string>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <sstream>


namespace network {

const std::uint8_t MAX_MASK_VALUE = 32;

class IP_Mask
{
public:
    IP_Mask() = default;
    IP_Mask(const IP_Mask& other) = default;


    explicit IP_Mask(uint8_t var);;
    explicit IP_Mask(const std::string& var);;


    void Mask(std::uint8_t value);

    void Mask(const std::string& value);

    std::size_t ShortRecord()const noexcept;
    std::string FullRecord() const noexcept;

    bool operator < (const IP_Mask& other) const;
    bool operator != (const IP_Mask& other) const;
    bool operator > (const IP_Mask& other) const;
private:

    using bit32 = std::bitset<32>;

    template <typename BitContainer>
    size_t countl_one(BitContainer value){

        size_t res{0};
        for(int  i = value.size() - 1 ; i >= 0; --i){
            if(!value[i])
                break;
            ++res;
        }
        return res;
    }

    template <typename T>
    void ValidationCheck(const T& var){
        if constexpr(std::is_same_v<T,std::uint8_t>){
            NumValidation(var);
        }else{
            StringValidation(var);
        }
    }

    std::string StringFromBits()const;

    std::size_t GetOctet(std::size_t number_of_octet) const;
    void NumValidation(std::uint8_t var);
    void StringValidation(const std::string& var);

    static  std::vector<std::uint8_t>StringsToNums(std::vector<std::string> strings);
    static  bit32 BitsFromNums(std::vector<std::uint8_t> nums);
    static  bit32 BitsFromMask(const std::string& mask);
private:
    bit32 bits;
    mutable  std::optional<std::string> string_form_;
};

}//namespace network


