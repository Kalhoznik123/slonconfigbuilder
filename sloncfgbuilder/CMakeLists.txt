cmake_minimum_required (VERSION 3.4...3.14)

# project (config_costructor VERSION 1.1.0)
set (BUILD_NAME slon_cfg)
set (Boost_USE_STATIC_LIBS ON)
find_package (Boost COMPONENTS program_options REQUIRED)
find_package (yaml-cpp REQUIRED)

set (SOURCE_FILES main.cpp
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
    src/ip_address.cpp
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
    src/detail.h
    src/parsers.h
    src/ip_address.h
)

add_executable (${BUILD_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_compile_options (${BUILD_NAME} PRIVATE -std=c++17)

if (Boost_FOUND)
    target_link_libraries (${BUILD_NAME} PRIVATE Boost::program_options)
endif ()

if (yaml-cpp_FOUND)
    target_link_libraries (${BUILD_NAME} PRIVATE yaml-cpp::yaml-cpp)
endif ()

add_subdirectory (arp)

target_include_directories (${BUILD_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/arp)
target_link_libraries (${BUILD_NAME} PRIVATE arp)
