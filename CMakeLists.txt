cmake_minimum_required(VERSION 3.10.0)
project(petal VERSION 0.1.0 LANGUAGES C CXX)

enable_testing()

add_subdirectory(tests)
add_library(petal petal.cpp)

