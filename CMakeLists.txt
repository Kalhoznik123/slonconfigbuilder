cmake_minimum_required(VERSION 3.16.0)
project(config_costructor VERSION 0.1.0)


list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
find_package(nlohmann_json 3.2.0 REQUIRED)

set(SOURCE_FILES  src/main.cpp 
									src/json_builder.cpp
									src/abonent.cpp
									src/arp.cpp
									src/config_builder.cpp
									src/interface_settings.cpp
									src/domain.cpp
)

set (HEADER_FILES src/json_builder.h
									src/abonent.h
									src/arp.h
									src/config_builder.h
									src/interface_settings.h
									src/domain.h)

add_executable(config_costructor ${SOURCE_FILES}  ${HEADER_FILES}  )

add_subdirectory(arp)

target_compile_options(${PROJECT_NAME} PRIVATE -std=c++17)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/arp)
target_link_libraries(${PROJECT_NAME} PRIVATE arp)