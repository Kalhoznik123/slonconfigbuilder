#pragma once
/*!
\file
\brief Заголовочный файл описывает внутренний и внений интерфейс.
*/
#include <algorithm>
#include <string>
/*!
    @brief Вид интерфейса.
*/
enum class InterfaceType {
  INET, ///< Указывает, что интерфейс внешний.
  LAN ///< Указывает, что интерфейс внеутренний.
};

/*!
    @brief Структура для описания интерфейсв(внешнего\внутреннего).
*/
struct InterfaceSettings {
  int speed{0};
  std::string mode;
  InterfaceType interface_type;
};
