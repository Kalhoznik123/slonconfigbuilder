cmake_minimum_required(VERSION 3.4...3.14)
project(config_costructor VERSION 1.1.0)

set(ENABLE_TESTS OFF)


find_package(nlohmann_json 3.2.0 REQUIRED)
find_package(Boost 1.82 COMPONENTS program_options REQUIRED)
find_package(yaml-cpp REQUIRED)

if(ENABLE_TESTS)
    add_subdirectory(test)
endif()


set(SOURCE_FILES  main.cpp
    src/json_builder.cpp
    src/abonent.cpp
    src/arp.cpp
    src/config_builder.cpp
    src/interface_settings.cpp
    src/domain.cpp
    src/cin_builder.cpp
    src/ip_mask.cpp
    src/abonent_remote.cpp
    src/yaml_builder.cpp
    )


set (HEADER_FILES src/json_builder.h
    src/abonent.h
    src/arp.h
    src/config_builder.h
    src/interface_settings.h
    src/domain.h
    src/IBuilder.h
    src/cin_builder.h
    src/ip_mask.h
    src/abonent_remote.h
    src/yaml_builder.h
    )

add_executable(config_costructor ${SOURCE_FILES}  ${HEADER_FILES} )
target_compile_options(${PROJECT_NAME} PRIVATE -std=c++17)

if(Boost_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE Boost::program_options)
endif()

if(nlohmann_json_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
endif()
if(yaml-cpp_FOUND)
     target_link_libraries(${PROJECT_NAME} PRIVATE yaml-cpp::yaml-cpp)
endif()

add_subdirectory(arp)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/arp)
target_link_libraries(${PROJECT_NAME} PRIVATE arp)


