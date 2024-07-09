#include <string>
#include <memory>
#include <fstream>
#include <iostream>
#include <type_traits>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include "src/detail.h"
#include "src/IBuilder.h"
#include "src/cin_builder.h"
#include "src/yaml_builder.h"
#include "src/json_builder.h"
#include "src/config_builder.h"

namespace prog_opt = boost::program_options;


//TODO: добавить тесты для конфиг билдера
//TODO добвить количество выведенных адресатов

int main(int argc, char** argv) {


    // TODO: добавить работу с разными стандартами(компиляторов)

    boost::program_options::options_description opt_desc = detail::MakeOptionDescription();

    const auto vm = detail::MakeAndFillVMap(opt_desc ,argc,argv);

    if (const auto it = vm.find("help"); it != vm.end()) {
        std::cout << opt_desc << std::endl;
        exit(0);
    }

    std::unique_ptr<IBuilder> builder;
    settings::Settings settings;

    settings = detail::ProcesingInputOptions(vm);

    const configurator::ConfigBuilder config_builder(settings);
    const std::string configuration = config_builder.Dump();

    if(const auto it = vm.find("verbose"); it != vm.end())
        std::cout << configuration << '\n';

    std::ofstream file(detail::ConfigFileName(vm), std::ios::out);
    file << configuration;

    if(const auto it = vm.find("description"); it != vm.end()){
        auto abonent_descriptions = config_builder.MakeDescriptions();
        std::cout << abonent_descriptions;
        std::cout << "------\n";
        std::cout << "Всего: "<< abonent_descriptions.size() << " description абонентов\n";
    }
}
