#include "json_builder.h"
#include <nlohmann/json.hpp>

void JsonBuilder::Parse(std::istream& in) {

using json = nlohmann::json;

json document = json::parse(in);

}
