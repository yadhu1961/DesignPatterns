cmake_minimum_required(VERSION 3.10)

project(pimpl
  VERSION
    1.0
  DESCRIPTION
    "Pointer to implementation example"
  LANGUAGES
    CXX
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(pimpl src/Pimpl.cpp src/Pimpl_test.cpp)

add_custom_command(
    TARGET pimpl
    POST_BUILD
    COMMAND bin/pimpl
    DEPENDS pimpl
    COMMENT "Running pimpl"
)