cmake_minimum_required(VERSION 3.31)
project(LinearSystemSolver)

set(CMAKE_CXX_STANDARD 23)

add_executable(LinearSystemSolver main.cpp
        include/Matrix.ipp
        include/Matrix.h
        include/Vector.ipp
        include/Vector.h
        include/Solver.h
        src/Solver.cpp
        include/Traits.h
        include/Config.h)

enable_testing()
add_subdirectory(tests)