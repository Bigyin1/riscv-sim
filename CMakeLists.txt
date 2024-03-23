cmake_minimum_required(VERSION 3.25)
project(riscv-model VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

include(cmake/CompileOptions.cmake)

enable_testing()
add_subdirectory(models/cpu)
add_subdirectory(models/ram)

add_subdirectory(tests)
