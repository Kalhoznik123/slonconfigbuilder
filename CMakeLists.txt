cmake_minimum_required(VERSION 3.16.0)
project(config_costructor VERSION 0.1.0)


#todo добавить условие для возможности создвать тесты

set(BOOST_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../lib_source/boost_lib/lib" CACHE STRING "Path to libs")
set(BOOST_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../lib_source/boost_lib/include/" CACHE STRING "Path to include")

set(ENABLE_TESTS ON)

message(STATUS ${BOOST_INCLUDE_DIR})
message(STATUS ${BOOST_LIB_DIR})


list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}")

find_package(nlohmann_json 3.2.0 REQUIRED)


if(ENABLE_TESTS)
    find_package(GTest)

    add_executable(test_gtest test/test.cpp
        src/json_builder.cpp
        src/abonent.cpp
        src/arp.cpp
        src/config_builder.cpp
        src/interface_settings.cpp
        src/domain.cpp
        src/cin_builder.cpp
        src/ip_mask.cpp
        src/json_builder.h
        src/abonent.h
        src/arp.h
        src/config_builder.h
        src/interface_settings.h
        src/domain.h
        src/IBuilder.h
        src/cin_builder.h
        src/ip_mask.h
        )


    target_compile_options(test_gtest PRIVATE -std=c++17)

    target_include_directories(test_gtest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/arp)
    #target_include_directories(test_gtest PRIVATE ${GTEST_INCLUDE_DIRS})


    target_link_libraries(test_gtest PRIVATE arp gtest gtest_main)
    target_link_libraries(test_gtest PRIVATE nlohmann_json::nlohmann_json)
    target_link_libraries(test_gtest PRIVATE ${GTEST_BOTH_LIBRARISE})

endif()


set(SOURCE_FILES  src/main.cpp 
    src/json_builder.cpp
    src/abonent.cpp
    src/arp.cpp
    src/config_builder.cpp
    src/interface_settings.cpp
    src/domain.cpp
    src/cin_builder.cpp
    src/ip_mask.cpp)


set (HEADER_FILES src/json_builder.h
    src/abonent.h
    src/arp.h
    src/config_builder.h
    src/interface_settings.h
    src/domain.h
    src/IBuilder.h
    src/cin_builder.h
    src/ip_mask.h )

add_executable(config_costructor ${SOURCE_FILES}  ${HEADER_FILES}  )

add_subdirectory(arp)

target_compile_options(${PROJECT_NAME} PRIVATE -std=c++17)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/arp)
target_include_directories(${PROJECT_NAME} PRIVATE ${BOOST_INCLUDE_DIR})


target_link_directories(${PROJECT_NAME} PRIVATE  ${BOOST_LIB_DIR} )


target_link_libraries(${PROJECT_NAME} PRIVATE arp)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PRIVATE boost_program_options)
