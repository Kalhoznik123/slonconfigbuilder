#include "IBuilder.h"
#include "cin_builder.h"
#include "config_builder.h"
#include "json_builder.h"
#include <gtest/gtest.h>
#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include<type_traits>

namespace prog_opt = boost::program_options;

std::string ConfigFileName(const prog_opt::variables_map& map){

    std::string name = "config.txt";

    if(const auto it = map.find("output-file");it != map.end())
        name  = it->second.as<std::string>();

    return name;
}

prog_opt::options_description MakeOptionDescription(){
    prog_opt::options_description desc{"Options"};

    desc.add_options()("help,h", "Help decsription")
            ("input-file,I", prog_opt::value<std::string>(),"Path to settings file")
            ("interactive,i", "Interactive mode")
            ("output-file,o",prog_opt::value<std::string>(),"Path to outpute file");

    return desc;
}


prog_opt::variables_map MakeAndFillVMap(const prog_opt::options_description& desc, int argc,  char** argv){

    prog_opt::variables_map vm;
    prog_opt::store(parse_command_line(argc, argv, desc), vm);
    prog_opt::notify(vm);
    return vm;
}


template<typename Builder, typename = std::enable_if<std::is_base_of_v<IBuilder,Builder >>>
settings::Settings MakeSettings(std::istream& in){

    std::unique_ptr<IBuilder> builder = std::make_unique<Builder>(in);
    settings::Settings  settings = builder->MakeSettings();

    return settings;
}


int main(int argc, char** argv) {


    // TODO: добавить verbose режим

    boost::program_options::options_description opt_desc = MakeOptionDescription();

    const auto vm = MakeAndFillVMap(opt_desc ,argc,argv);
    std::unique_ptr<IBuilder> builder;

    settings::Settings settings;

    if (const auto it = vm.find("help"); it != vm.end()) {
        std::cout << opt_desc << std::endl;
        exit(0);
    }
    if (const auto it = vm.find("input-file"); it != vm.end()) {
        std::ifstream in_file(it->second.as<std::string>(), std::ios::in);
        settings = MakeSettings<JsonBuilder>(in_file);
    } else if (const auto it = vm.find("interactive"); it != vm.end()) {
        settings = MakeSettings<Cin_builder>(std::cin);;
    }else{
        exit(0);
    }
    const configurator::ConfigBuilder config_builder(settings);

    std::ofstream file(ConfigFileName(vm), std::ios::out);

    file << config_builder.Dump() << std::endl;
}
