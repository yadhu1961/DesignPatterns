cmake_minimum_required(VERSION 3.10)

# set the project name
project(PolicyBasedStrategyPattern VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

set(src_files src/test_driver.cpp)

# add the executable
add_executable(PolicyBasedStrategyPattern.out ${src_files})

