cmake_minimum_required(VERSION 4.0)
project(cpd)

set(CMAKE_CXX_STANDARD 20)
set(EXECUTABLE_OUTPUT_PATH cpd)

add_executable(cpd main.cpp
        struct_e_parsing.h
        struct_e_parsing.cpp
        defs_gerais_e_cartas.h
        defs_gerais_e_cartas.cpp
        colors.h
        colors.cpp
        arvores_e_organizacao.h
        arvores_e_organizacao.cpp
        search.h
        search.cpp)
find_package(cjSON CONFIG REQUIRED)
target_link_libraries(cpd PRIVATE cjson)
