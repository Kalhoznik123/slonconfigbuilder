#include <iostream>
#include <string>
#include "config_builder.h"
#include "json_builder.h"
#include <fstream>

int main(int, char**) {


std::ifstream in("settings.json",std::ios::in);


JsonBuilder buider(in);

buider.MakeSettings();



}
