cmake_minimum_required(VERSION 3.29)
project(spline)

set(CMAKE_CXX_STANDARD 20)

add_library(spline SHARED library.cpp)

# Add Eigen3 library for matrix operations
find_package(Eigen3 REQUIRED)
target_include_directories(spline PRIVATE ${EIGEN3_INCLUDE_DIR})