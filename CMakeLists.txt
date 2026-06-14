cmake_minimum_required(VERSION 3.31)
project(LinearSystemSolver)

set(CMAKE_CXX_STANDARD 23)

add_executable(LinearSystemSolver main.cpp
        src/Matrix.cpp
        include/Matrix.h
        include/Vector.ipp
        include/Vector.h)

enable_testing()
add_subdirectory(tests)