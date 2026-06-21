cmake_minimum_required(VERSION 3.16)
project(PROBE_NAME LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(PROBE_NAME main.cpp)
add_executable(PROBE_NAME_tests tests/test_main.cpp)

enable_testing()
add_test(NAME PROBE_NAME_tests COMMAND PROBE_NAME_tests)
