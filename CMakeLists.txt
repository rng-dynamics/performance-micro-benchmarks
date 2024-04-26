cmake_minimum_required(VERSION 3.16)
project(performance-micro-benchmarks VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
endif()
message(STATUS "CMAKE_BUILD_TYPE = [${CMAKE_BUILD_TYPE}]")

include("cmake/dependencies.cmake")

add_subdirectory("benchmark/")
add_subdirectory("src/")
add_subdirectory("test/unit/")
add_subdirectory("support-library/")
