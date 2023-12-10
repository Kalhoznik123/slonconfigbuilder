#pragma once
/*!
\file
\brief Заголовочный файл описывает маску подсети.
*/
#include <optional>
#include <bitset>
#include <string>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <string_view>


namespace network {

const std::uint8_t MAX_MASK_VALUE = 32; ///< Переменная для указания максимальной длинны мыски подсети.
/*!
    @brief Класс описывает маску подсети
*/
class IP_Mask
{
public:
    IP_Mask() = default;
    IP_Mask(const IP_Mask& other) = default;


    explicit IP_Mask(uint8_t var);;
    explicit IP_Mask(std::string_view var);;

    /*!
@brief Функция устанавливает значение маски.
@param value - значение маски в виде числа.
*/
    void Mask(std::uint8_t value);
    /*!
@brief Функция устанавливает значение маски.
@param value - значение маски в виде строки.
*/
    void Mask(const std::string& value);
    /*!
@brief Функция вычисляет значение маски подсети в виде числа.
@return Возвращает число, как значение маски.
*/
    std::size_t ShortRecord()const noexcept;
    /*!
@brief Функция вычисляет значение маски подсети в виде строки.
@return Возвращает число, как значение строки.
*/
    std::string FullRecord() const noexcept;
    /*!
@brief Функция сравнение на меньше.
@return Возвращает результат стравнения.
*/
    bool operator < (const IP_Mask& other) const;
    /*!
@brief Функция не равно.
@return Возвращает результат стравнения.
*/
    bool operator != (const IP_Mask& other) const;
    /*!
@brief Функция сравнение на больше.
@return Возвращает результат стравнения.
*/
    bool operator > (const IP_Mask& other) const;
    /*!
@brief Функция сравнение на равно.
@return Возвращает результат стравнения.
*/
    bool operator == (const IP_Mask& other) const;
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
    void StringValidation(std::string_view var);

    static  std::vector<std::uint8_t>StringsToNums(std::vector<std::string> strings);
    static  bit32 BitsFromNums(std::vector<std::uint8_t> nums);
    static  bit32 BitsFromMask(std::string_view mask);
private:
    bit32 bits;
    mutable  std::optional<std::string> string_form_;
};

}//namespace network


