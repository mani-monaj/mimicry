cmake_minimum_required(VERSION 2.6)

project(mimicry)

set(mimicry_HEADERS src/ds.h)
set(mimicry_SOURCES src/mimicry.cpp src/ds.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

add_executable(mimicry
    ${mimicry_HEADERS}
    ${mimicry_SOURCES}
)
