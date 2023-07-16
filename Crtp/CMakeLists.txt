cmake_minimum_required(VERSION 3.10)

project(Crtp
  VERSION
    1.0
  DESCRIPTION
    "Curiously Recurring Template Pattern"
  LANGUAGES
    CXX
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(crtp src/Crtp.cpp)

add_custom_command(
    TARGET crtp
    POST_BUILD
    COMMAND bin/crtp
    DEPENDS crtp
    COMMENT "Running Curiously Recurring Template Pattern example"
)