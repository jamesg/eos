cmake_minimum_required(VERSION 2.6)
project(Raytracer)
enable_testing()

find_package(Eigen3)

set(CMAKE_CXX_FLAGS "-std=c++0x")
include_directories("/usr/include/eigen3")

include_directories("src")

file(GLOB raytracer_lib_sources src/*.cpp)
add_library(raytracer-lib ${raytracer_lib_sources})

add_executable(raytracer "src/raytracer/main.cpp")
target_link_libraries(raytracer raytracer-lib)

file(GLOB raytracer_test_sources src/test/*.cpp)
add_executable(test-raytracer ${raytracer_test_sources})
target_link_libraries(test-raytracer raytracer-lib)

