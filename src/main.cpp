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


std::string ConfigFileName(const boost::program_options::variables_map& map){

    std::string name = "config.txt";

    if(const auto it = map.find("output-file");it != map.end())
        name  = it->second.as<std::string>();

    return name;
}

boost::program_options::options_description MakeOptionDescription(){
    boost::program_options::options_description desc{"Options"};

    desc.add_options()("help,h", "Help decsription")
            ("input-file,I", boost::program_options::value<std::string>(),"Path to settings file")
            ("interactive,i", "Interactive mode")
            ("output-file,o",boost::program_options::value<std::string>(),"Path to outpute file");

    return desc;
}


boost::program_options::variables_map MakeAndFillVMap(const boost::program_options::options_description& desc, int argc,  char** argv){

    boost::program_options::variables_map vm;
    boost::program_options::store(parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);
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
    // JsonBuilder builder(std::cin);
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
