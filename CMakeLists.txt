cmake_minimum_required(VERSION 2.6)
project(Raytracer)

find_package(Eigen3)

file(GLOB raytracer_sources src/*.cpp)
add_executable(raytracer ${raytracer_sources})
#target_link_libraries(
    #raytracer
    #)

