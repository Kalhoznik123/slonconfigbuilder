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
#include "src/detail.h"

namespace prog_opt = boost::program_options;



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

    settings = detail::ProsesingInputOptions(vm);

    const configurator::ConfigBuilder config_builder(settings);
    const std::string configuration = config_builder.Dump();

    if(const auto it = vm.find("verbose"); it != vm.end())
        std::cout << configuration << '\n';

    std::ofstream file(detail::ConfigFileName(vm), std::ios::out);
    file << configuration;



    auto abonent_descriptions = config_builder.MakeDescriptions();
    if(!abonent_descriptions.empty())
        std::cout << abonent_descriptions;
}
