#pragma once
/*!
\file
\brief Заголовочный файл описывает интерфейс для работы с разными классами- считывателями(из json/yaml/потока).
*/
#include "domain.h"
/*!
    @brief Класс-интерфейс для разных классов-считывателей.
*/
class IBuilder {

public:
  virtual ~IBuilder(){

  };

  virtual settings::Settings MakeSettings() = 0;
};
