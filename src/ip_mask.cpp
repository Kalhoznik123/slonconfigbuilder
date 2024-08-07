#include <sstream>
#include <iostream>
#include <algorithm>
#include <exception>
#include <string_view>
#include "ip_mask.h"



namespace network {

std::vector<std::string> Split(std::string_view str,std::string_view delimiter){
    size_t pos_start = 0, pos_end = 0, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = str.find(delimiter, pos_start)) != std::string::npos) {
        token = str.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (std::string(str.substr (pos_start)));
    return res;

}


IP_Mask::bit32_t IP_Mask::BitsFromMask(std::string_view mask){

    std::vector<std::string> num_from_mask = Split(mask,".");
    std::vector<std::uint8_t> nums = StringsToNums(std::move(num_from_mask));

    bit32_t bit_res = BitsFromNums(std::move(nums));

    return bit_res;

}

IP_Mask::bit32_t IP_Mask::BitsFromNums(std::vector<uint8_t> nums){
    bit32_t res;

    std::uint8_t shift = MAX_MASK_LENGTH;

    for(std::uint8_t num: nums){

        res |= bit32_t(num) << shift;
        if(shift!=0){
            shift-=OCTET_LENGTH;
        }

    }
    return res;
}

std::vector<uint8_t> IP_Mask::StringsToNums(std::vector<std::string> strings){
    std::vector<std::uint8_t> nums;
    nums.reserve(strings.size());
    std::transform(strings.begin(),strings.end(),std::back_inserter<std::vector<std::uint8_t>>(nums),
                   [](const auto& str){
        return static_cast<std::uint8_t>(std::stoi(str));
    });

    return nums;
}



IP_Mask::IP_Mask(uint8_t var){
    ValidationCheck(var);
}

IP_Mask::IP_Mask(std::string_view var) : string_form_(var) {
  ValidationCheck(var);
}

void IP_Mask::Mask(uint8_t value){
    ValidationCheck(value);
    string_form_.reset();
}

void IP_Mask::Mask(std::string_view value){
    ValidationCheck(value);
    string_form_ = std::string(value);
}

std::size_t IP_Mask::ShortRecord() const noexcept{
    return bits.count();
}



std::string IP_Mask::FullRecord() const noexcept{

    if(!string_form_.has_value())
        string_form_ = StringFromBits();
    return *string_form_;
}

bool IP_Mask::operator <(const IP_Mask &other) const {
    return this->ShortRecord() > other.ShortRecord();
}

bool IP_Mask::operator !=(const IP_Mask &other) const{
    return this->ShortRecord() != other.ShortRecord();
}

bool IP_Mask::operator >(const IP_Mask &other) const{
    return !(*this < other);
}

bool IP_Mask::operator ==(const IP_Mask &other) const{
    return this->ShortRecord() == other.ShortRecord();
}

std::string IP_Mask::StringFromBits() const {
    std::ostringstream out;
    const char dot = '.';

    for(std::uint8_t  i = 0 + 1 ; i < 5; ++i){
        if(i!=4){
            out<<GetOctet(static_cast<std::size_t>(i)) << dot;
        }else
            out<<GetOctet(static_cast<std::size_t>(i));
    }
    return out.str();
}

std::size_t IP_Mask::GetOctet(std::size_t number_of_octet) const {
    size_t value;
    const auto num = bits.to_ullong();

    switch (number_of_octet) {
    case 1:
        value = (num & 0xff000000UL) >>24;
        break;
    case 2:
        value = (num & 0x00ff0000UL) >> 16;
        break;
    case 3:
        value = (num & 0x0000ff00UL) >>8;
        break;
    case 4:
        value = num & 0x000000ffUL;
        break;
    default:
        throw std::out_of_range("count out of range");
    }
    return value;
}



void IP_Mask::NumValidation(std::uint8_t var) {

    if(var > 32)
        throw std::invalid_argument("mask is invalid");
    bits = 0xffffffffUL << (MAX_MASK_VALUE - var);
}

void IP_Mask::StringValidation(std::string_view var) {
    bit32_t bit_res = BitsFromMask(var);

    const size_t one_count = bit_res.count();


    const size_t lcount = countl_one(std::move(bit_res));
    if(one_count != lcount)
        throw std::invalid_argument("mask is invalid");
    bits = 0xffffffffUL << (MAX_MASK_VALUE - lcount);
}
}
