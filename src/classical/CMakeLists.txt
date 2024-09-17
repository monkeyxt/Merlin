cmake_minimum_required(VERSION 3.19)
project(Merlin)
set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH "../../bin")
include_directories(src/classical)
add_executable(Arthur
        certificate.hpp
        greedy.cpp
        greedy.hpp
        instance.hpp
        local.cpp
        local.hpp
        arthur.cpp
        types.hpp
        instance.cpp
        certificate.cpp)
