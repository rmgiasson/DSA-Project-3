cmake_minimum_required(VERSION 3.27)
project(DSA_Project_3)

set(CMAKE_CXX_STANDARD 14)

include_directories(src_updated)

add_executable(DSA_Project_3
        src_updated/main.cpp
        src_updated/mapStructure.hpp
        src_updated/unorderedMapStructure.hpp
        src_updated/genrePredictor.hpp
        src_updated/genrePredictor.cpp
        src_updated/topTen.hpp
        src_updated/wordPerGenre.hpp
)
