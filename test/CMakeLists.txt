
find_package(Threads REQUIRED)
find_package(GTest)
find_package(nlohmann_json 3.2.0 REQUIRED)
find_package(Boost 1.82 COMPONENTS program_options REQUIRED)

set(TEST-SOURCES-PATTERN "${PROJECT_SOURCE_DIR}/src/*.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.11)
    list(INSERT TEST-SOURCES-PATTERN 0 CONFIGURE_DEPENDS)
endif()

file(GLOB TEST-SOURCES ${TEST-SOURCES-PATTERN})

add_executable(config_gtest "")
target_sources(config_gtest PRIVATE  test.cpp ${TEST-SOURCES})
#add_executable(config_gtest test.cpp
#    ${PROJECT_SOURCE_DIR}/src/json_builder.cpp
#   ${PROJECT_SOURCE_DIR}/src/abonent.cpp
#  ${PROJECT_SOURCE_DIR}/src/arp.cpp
# ${PROJECT_SOURCE_DIR}/src/config_builder.cpp
#    ${PROJECT_SOURCE_DIR}/src/interface_settings.cpp
#   ${PROJECT_SOURCE_DIR}/src/domain.cpp
#  ${PROJECT_SOURCE_DIR}/src/cin_builder.cpp
# ${PROJECT_SOURCE_DIR}/src/ip_mask.cpp
#    ${PROJECT_SOURCE_DIR}/src/abonent_remote.cpp
#   )
target_compile_options(config_gtest PRIVATE -std=c++17)
target_include_directories(config_gtest PRIVATE ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/arp)

if(Boost_FOUND)
    target_link_libraries(config_gtest PRIVATE Boost::program_options)
endif()

if(nlohmann_json_FOUND)
    target_link_libraries(config_gtest PRIVATE nlohmann_json::nlohmann_json)
endif()

if(Threads_FOUND)
    target_link_libraries(config_gtest PRIVATE arp gtest gmock Threads::Threads)
else()
    target_link_libraries(config_gtest PRIVATE arp gtest gmock)
endif()

target_link_libraries(config_gtest PRIVATE arp )


