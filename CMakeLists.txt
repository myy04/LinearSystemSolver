cmake_minimum_required(VERSION 3.31)
project(LinearSystemSolver)

set(CMAKE_CXX_STANDARD 23)

add_executable(LinearSystemSolver main.cpp
        Matrix.cpp
        Matrix.h)
