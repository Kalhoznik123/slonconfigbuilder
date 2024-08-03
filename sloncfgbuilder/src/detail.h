#pragma once
#include "IBuilder.h"
#include "cin_builder.h"
#include "config_builder.h"
#include "json_builder.h"
#include "yaml_builder.h"
#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>
#include <fstream>

namespace prog_opt = boost::program_options;

inline std::ostream &operator<<(std::ostream &out,
                                const std::vector<std::string> &container) {
  for (auto &val : container) {
    out << val << std::endl;
  }
  return out;
}

namespace detail {

template <typename Builder, typename = std::enable_if<
                                std::is_constructible_v<Builder, std::istream>>>
settings::Settings MakeSettings(std::istream &in) {

  std::unique_ptr<IBuilder> builder = std::make_unique<Builder>(in);
  settings::Settings settings = builder->MakeSettings();

  return settings;
}

template <typename Builder, typename = std::enable_if<
                                std::is_constructible_v<Builder, std::string>>>
settings::Settings MakeSettings(std::string_view file_name) {

  std::unique_ptr<IBuilder> builder =
      std::make_unique<Builder>(std::string(file_name));
  settings::Settings settings = builder->MakeSettings();

  return settings;
}

inline std::string ConfigFileName(const prog_opt::variables_map &map) {

  std::string name = "config.txt";

  if (const auto it = map.find("output-file"); it != map.end())
    name = it->second.as<std::string>();

  return name;
}

inline prog_opt::options_description MakeOptionDescription() {
  prog_opt::options_description desc{"Options"};

  desc.add_options()("help,h", "Help decsription")(
      "input-file,I", prog_opt::value<std::string>(),
      "Path to settings file")("interactive,i", "Interactive mode")(
      "output-file,o", prog_opt::value<std::string>(), "Path to outpute file")(
      "verbose,v", "Verbose mode")("description,d", "Description mode");

  return desc;
}

inline prog_opt::variables_map
MakeAndFillVMap(const prog_opt::options_description &desc, int argc,
                char **argv) {
  prog_opt::variables_map vm;
  prog_opt::store(parse_command_line(argc, argv, desc), vm);
  prog_opt::notify(vm);
  return vm;
}

inline settings::Settings GetSettingsFromFile(std::string_view file_name) {

  std::ifstream in_file(file_name.data(), std::ios::in);
  settings::Settings result;

  if (boost::ends_with(file_name, "json")) {
    result = MakeSettings<builder::FromJsonBuilder>(in_file);
  } else {
    result = MakeSettings<builder::FromYamlBuilder>(in_file);
  }
  return result;
}

inline char GetCharFromStream() {
  char result = 0;
  std::cin >> result;
  std::cin.putback(result);
  return result;
}

inline settings::Settings
ProcesingInputOptions(const prog_opt::variables_map &map) {

  settings::Settings result;

  if (const auto it = map.find("input-file"); it != map.end()) {

    const std::string in_file_name = it->second.as<std::string>();
    result = GetSettingsFromFile(in_file_name);

  } else if (const auto it = map.find("interactive"); it != map.end()) {
    result = MakeSettings<builder::FromCinBuilder>(std::cin);
    ;
  } else {
    const char marker = detail::GetCharFromStream();
    if (marker == '{') {
      result = MakeSettings<builder::FromJsonBuilder>(std::cin);
    } else {
      result = MakeSettings<builder::FromYamlBuilder>(std::cin);
    }
  }
  return result;
}

} // namespace detail
