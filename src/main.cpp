#include <iostream>
#include <string>
#include "config_builder.h"
#include "json_builder.h"
#include <fstream>
int main(int, char**) {

//TODO: сделать адереса как класс с проверками и все такое
//TODO: сделать аппер кейс у арп адерсов

JsonBuilder builder(std::cin);

const auto settings  = builder.MakeSettings();

ConfigBuilder config_builder(settings);

//std::cout << config_builder.Dump() << std::endl;
std::ofstream file("config.txt", std::ios::out);

file << config_builder.Dump() << std::endl;

}
