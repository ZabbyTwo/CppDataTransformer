cmake_minimum_required(VERSION 3.23)

project(CppDataTransformer)

add_executable(CppDataTransformer)

target_sources(CppDataTransformer
    PRIVATE
    src/main.cpp
    src/csvFile/csvFile.cpp
    src/csvFile/csvFile.hpp
    src/tests/csvFileUnitTests.cpp
)