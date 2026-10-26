cmake_minimum_required(VERSION 3.23)

project(CppDataTransformer)

add_executable(CppDataTransformer)

target_sources(CppDataTransformer
    PRIVATE
    src/main.cpp
    src/dataTransformer/dataTransformer.cpp
    src/dataTransformer/dataTransformer.hpp
    src/tests/unitTests.cpp
    src/tests/unitTests.hpp
)