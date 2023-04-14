cmake_minimum_required(VERSION 3.16.0)
project(config_costructor VERSION 0.1.0)


list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
find_package(nlohmann_json 3.2.0 REQUIRED)

add_executable(config_costructor src/main.cpp 
														src/json_builder.cpp
														src/abonent.cpp
														src/arp.cpp
														src/config_builder.cpp
														src/lan_config.cpp
														src/domain.cpp
														)



target_compile_options(${PROJECT_NAME} PRIVATE -std=c++17)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)