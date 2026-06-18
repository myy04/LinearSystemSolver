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

# Compile bindings.cpp as a Python module
pybind11_add_module(bindings
        python-binding/bindings.cpp
        src/GaussianSolver.cpp
)

# Optional: Output the compiled Python library directly into the tests folder
# so `testing_bindings.py` can automatically find `bindings.so` or `bindings.dylib`.
set_target_properties(bindings PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/tests)