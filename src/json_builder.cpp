#include "json_builder.h"
#include "domain.h"
#include <nlohmann/json.hpp>



void JsonBuilder::Parse() {

  document_ = json::parse(in_);

}

settings::Settings JsonBuilder::MakeSettings()
{

settings::Settings settings;

if(document_.is_null()){
  Parse();
}

if(const auto it = document_.find("internal.address");it != document_.end()){
  std::cout << it->at("address").get<std::string>()<< std::endl;
}




return settings::Settings();
}
