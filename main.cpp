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
#include"src/detail.h"
namespace prog_opt = boost::program_options;



int main(int argc, char** argv) {


    // TODO: добавить работу с разными стандартами(компиляторов)
    // TODO: изменить сигнатуру сеттингса на optionals т.к некоторых пунктов может и не быть
    // TODO: изменить конфиг билдер под новые settings

    boost::program_options::options_description opt_desc = detail::MakeOptionDescription();

    const auto vm = detail::MakeAndFillVMap(opt_desc ,argc,argv);

    if (const auto it = vm.find("help"); it != vm.end()) {
        std::cout << opt_desc << std::endl;
        exit(0);
    }

    std::unique_ptr<IBuilder> builder;
    settings::Settings settings;

    settings = detail::ProsesingInputOptions(vm);

//    if (const auto it = vm.find("input-file"); it != vm.end()) {

//        const std::string in_file_name = it->second.as<std::string>();
//        settings = detail::GetSettingsFromFile(in_file_name);

//    }else if (const auto it = vm.find("interactive"); it != vm.end()) {
//        settings = detail::MakeSettings<builder::FromCinBuilder>(std::cin);;
//    }else{
//        const char marker = detail::GetCharFromStream();
//        if(marker == '{'){
//            settings = detail::MakeSettings<builder::FromJsonBuilder>(std::cin);
//        }else{
//            settings = detail::MakeSettings<builder::FromYamlBuilder>(std::cin);
//        }
//    }

    const configurator::ConfigBuilder config_builder(settings);
    const std::string configuration = config_builder.Dump();

    if(const auto it = vm.find("verbose"); it != vm.end())
        std::cout << configuration << '\n';

    std::ofstream file(detail::ConfigFileName(vm), std::ios::out);
    file << configuration << std::endl;
}
