cmake_minimum_required(VERSION 3.27)
project(DSA_Project_3)

set(CMAKE_CXX_STANDARD 14)

include_directories(src_updated)

add_executable(DSA_Project_3
        src_updated/main.cppcmake_minimum_required(VERSION 3.27)
project(DSA_Project_3)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(DSA_Project_3
        src/main.cpp
        src/mapStructure.hpp
        src/unorderedMapStructure.hpp
        src/genrePredictor.hpp
        src/test.cpp
        src/genrePredictor.cpp
        src/topTen.hpp
        src/wordPerGenre.hpp
)

        src_updated/mapStructure.hpp
        src_updated/unorderedMapStructure.hpp
        src_updated/genrePredictor.hpp
        src_updated/genrePredictor.cpp
)
