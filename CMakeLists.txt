cmake_minimum_required(VERSION 3.10)

project(DesignPatterns
  VERSION
    1.0
  DESCRIPTION
    "Design patterns repo"
  LANGUAGES
    CXX
)

add_subdirectory(Crtp)
add_subdirectory(pimpl)
add_subdirectory(PolicyBasedStrategyPattern)
add_subdirectory(strategy_pattern)

