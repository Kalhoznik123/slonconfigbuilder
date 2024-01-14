#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include "src/IBuilder.h"
#include "src/yaml_builder.h"
#include "src/cin_builder.h"
#include "src/config_builder.h"
#include "src/json_builder.h"

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
            ("output-file,o",prog_opt::value<std::string>(),"Path to outpute file")
            ("verbose,v","Verbose mode");

    return desc;
}


prog_opt::variables_map MakeAndFillVMap(const prog_opt::options_description& desc, int argc,  char** argv){

    prog_opt::variables_map vm;
    prog_opt::store(parse_command_line(argc, argv, desc), vm);
    prog_opt::notify(vm);
    return vm;
}


template<typename Builder, typename = std::enable_if<std::is_constructible_v<Builder, std::istream>>>
settings::Settings MakeSettings(std::istream& in){

    std::unique_ptr<IBuilder> builder = std::make_unique<Builder>(in);
    settings::Settings  settings = builder->MakeSettings();

    return settings;
}
template<typename Builder, typename = std::enable_if<std::is_constructible_v<Builder, std::string>>>
settings::Settings MakeSettings(std::string_view file_name){

    std::unique_ptr<IBuilder> builder = std::make_unique<Builder>(std::string(file_name));
    settings::Settings  settings = builder->MakeSettings();

    return settings;
}


int main(int argc, char** argv) {


    // TODO: посмотреть какие методы классов можно сделать noexept
    // TODO: добавить работу с разными стандартами(компиляторов)
    // TODO: изменить сигнатуру сеттингса на optionals т.к некоторых пунктов может и не быть
    // TODO: изменить yaml_builer для работы с потоком
    // TODO: изменить конфиг билдер под новые settings

    boost::program_options::options_description opt_desc = MakeOptionDescription();

    const auto vm = MakeAndFillVMap(opt_desc ,argc,argv);

    if (const auto it = vm.find("help"); it != vm.end()) {
        std::cout << opt_desc << std::endl;
        exit(0);
    }

    std::unique_ptr<IBuilder> builder;
    settings::Settings settings;

    if (const auto it = vm.find("input-file"); it != vm.end()) {
        const std::string in_file_name = it->second.as<std::string>();

        std::ifstream in_file(in_file_name, std::ios::in);

        if(boost::ends_with(in_file_name,"json")){
            settings = MakeSettings<builder::FromJsonBuilder>(in_file);
        }else{
            settings = MakeSettings<builder::FromYamlBuilder>(in_file);
        }

    }else if (const auto it = vm.find("interactive"); it != vm.end()) {
        settings = MakeSettings<builder::FromCinBuilder>(std::cin);;
    }else{
        char marker;
        std::cin >> marker;
        if(marker == '{'){
            std::cin.putback(marker);
            settings = MakeSettings<builder::FromJsonBuilder>(std::cin);
        }else{
            std::cin.putback(marker);
            settings = MakeSettings<builder::FromYamlBuilder>(std::cin);
        }
    }

    const configurator::ConfigBuilder config_builder(settings);
    const std::string configuration = config_builder.Dump();

    if(const auto it = vm.find("verbose"); it != vm.end())
        std::cout << configuration << '\n';

    std::ofstream file(ConfigFileName(vm), std::ios::out);
    file << configuration << std::endl;
}
