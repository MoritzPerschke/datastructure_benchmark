cmake_minimum_required(VERSION 3.22.1)
project(operation_benchmark)

set_property(GLOBAL PROPERTY CXX_STANDARD)

add_executable(benchmark benchmark.cpp)