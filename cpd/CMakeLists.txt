cmake_minimum_required(VERSION 4.0)
project(cpd)

set(CMAKE_CXX_STANDARD 20)
set(EXECUTABLE_OUTPUT_PATH cpd)

add_executable(cpd main.cpp
        struct_e_parsing.h
        struct_e_parsing.cpp)

