cmake_minimum_required(VERSION 3.10)

project(PolicyBasedStrategyPattern
  VERSION
    1.0
  DESCRIPTION
    "Policy based strategy pattern"
  LANGUAGES
    CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(src_files src/test_driver.cpp)

# add the executable
add_executable(PolicyBasedStrategyPattern ${src_files})

add_custom_command(
    TARGET PolicyBasedStrategyPattern
    POST_BUILD
    COMMAND bin/PolicyBasedStrategyPattern
    DEPENDS PolicyBasedStrategyPattern
    COMMENT "Running PolicyBasedStrategyPattern example"
)

