cmake_minimum_required(VERSION 3.10)

project(StrategyPattern
  VERSION
    1.0
  DESCRIPTION
    "Strategy pattern"
  LANGUAGES
    CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(src_files src/Duck_test.cpp src/Duck.cpp src/IDisplayBehaviour.cpp src/IFlyBehaviour.cpp src/SimpleDisplay.cpp src/SimpleFly.cpp)

# add the executable
add_executable(StrategyPattern ${src_files})

add_custom_command(
    TARGET StrategyPattern
    POST_BUILD
    COMMAND bin/StrategyPattern
    DEPENDS StrategyPattern
    COMMENT "Running StrategyPattern example"
)

