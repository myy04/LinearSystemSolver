cmake_minimum_required(VERSION 3.31)
project(LinearSystemSolver)

set(CMAKE_CXX_STANDARD 23)

if(APPLE)
    list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew")
endif()

find_package(GTest REQUIRED)

# ---- Your library / header ----
add_library(Vector INTERFACE)
target_include_directories(Vector INTERFACE ${CMAKE_SOURCE_DIR}/include)

# ---- Test executable ----
enable_testing()
add_executable(vector_tests test_vector.cpp)
target_link_libraries(vector_tests Vector GTest::gtest_main)

# ---- Matrix test executable ----
add_executable(matrix_tests test_matrix.cpp)
target_link_libraries(matrix_tests Vector GTest::gtest_main)

# ---- GaussianSolver test executable ----
add_executable(gaussian_solver_tests test_gaussian_solver.cpp ../src/GaussianSolver.cpp)
target_link_libraries(gaussian_solver_tests Vector GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(vector_tests)
gtest_discover_tests(matrix_tests)
gtest_discover_tests(gaussian_solver_tests)