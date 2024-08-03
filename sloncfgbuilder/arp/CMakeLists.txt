cmake_minimum_required (VERSION 3.16.0)


add_library (arp ARP.cpp ARP.h)
target_compile_options (arp PRIVATE -std=c++17)
