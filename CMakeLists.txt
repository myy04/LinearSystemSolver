cmake_minimum_required(VERSION 3.31)
project(LinearSystemSolver)

set(CMAKE_CXX_STANDARD 23)

add_executable(LinearSystemSolver main.cpp
        include/Matrix.ipp
        include/Matrix.h
        include/Vector.ipp
        include/Vector.h
        include/Solver.h
        include/Traits.h
        include/Config.h
        src/GaussianSolver.cpp
        include/GaussianSolver.h)

enable_testing()
add_subdirectory(tests)

# Find pybind11 (make sure you've installed it, e.g., `pip install pybind11`)
find_package(pybind11 REQUIRED)

# Compile bindings.cpp as a Python module using a distinct target name
pybind11_add_module(LinearSystemSolver_py
        src/bindings.cpp
        src/GaussianSolver.cpp
)

# Set OUTPUT_NAME to what Python expects ("LinearSystemSolver")
# and set the directory to the tests folder
set_target_properties(LinearSystemSolver_py PROPERTIES
        OUTPUT_NAME "LinearSystemSolver"
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/python
)