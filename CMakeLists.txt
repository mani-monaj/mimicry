cmake_minimum_required(VERSION 2.6)

project(mimicry)

set(myproject_HEADERS )
set(myproject_SOURCES src/mimicry.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

add_executable(mimicry
    ${myproject_SOURCES}
    ${myproject_MOC}
)
