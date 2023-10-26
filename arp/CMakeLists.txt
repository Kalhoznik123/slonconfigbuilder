cmake_minimum_required(VERSION 3.16.0)
project(arp VERSION 0.1.0)
enable_testing()

add_library(arp ARP.cpp ARP.h)
target_compile_options(arp  PRIVATE -std=c++14)
