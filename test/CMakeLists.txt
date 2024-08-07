find_package (Threads REQUIRED)
find_package (GTest)
find_package (Boost COMPONENTS program_options REQUIRED)
find_package (yaml-cpp REQUIRED)
enable_testing ()

set (THREADS_PREFER_PTHREAD_FLAG ON)
set (TEST-SOURCES-PATTERN "${PROJECT_SOURCE_DIR}/src/*.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.11)
    list (INSERT TEST-SOURCES-PATTERN 0 CONFIGURE_DEPENDS)
endif ()

file (GLOB TEST-SOURCES ${TEST-SOURCES-PATTERN})
add_executable (config_gtest "")
target_sources (config_gtest PRIVATE test.cpp ${TEST-SOURCES})

target_compile_options (config_gtest PRIVATE -std=c++17)
target_include_directories (config_gtest PRIVATE ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/arp)

if (Boost_FOUND)
    target_link_libraries (config_gtest PRIVATE Boost::program_options)
endif ()

if (Threads_FOUND)
    target_link_libraries (config_gtest PRIVATE arp gtest gmock Threads::Threads)
else ()
    target_link_libraries (config_gtest PRIVATE arp gtest gmock)
endif ()

if (yaml-cpp_FOUND)
    target_link_libraries (config_gtest PRIVATE yaml-cpp::yaml-cpp)
endif ()

target_link_libraries (config_gtest PRIVATE arp)

include (GoogleTest)
gtest_discover_tests (config_gtest)
