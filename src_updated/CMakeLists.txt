cmake_minimum_required(VERSION 3.27)
project(DSA_Project_3)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(DSA_Project_3
        src/main.cpp
        src/mapStructure.hpp
        src/unorderedMapStructure.hpp
        src/genrePredictor.hpp
)
