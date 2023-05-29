#include <iostream>
#include <string>
#include <fstream>
#include <boost/program_options.hpp>
#include "config_builder.h"
#include "json_builder.h"


int main(int, char**) {


//TODO: попробовать совместить с передачей по компорту


JsonBuilder builder(std::cin);

const auto settings  = builder.MakeSettings();

const configurator::ConfigBuilder config_builder(settings);

std::ofstream file("config.txt", std::ios::out);

file << config_builder.Dump() << std::endl;

}
