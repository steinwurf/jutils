cmake_minimum_required (VERSION 3.10)
project(jutils)

file(GLOB_RECURSE jutils_sources ./src/*.cpp)

add_library(jutils STATIC ${jutils_sources})
add_library(steinwurf::jutils ALIAS jutils)

target_include_directories(jutils INTERFACE src/)

target_compile_features(jutils PUBLIC cxx_std_11)
