cmake_minimum_required(VERSION 2.8)																			
project(gxx)		

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
include_directories(".")

file(GLOB SOURCE_LIB
    "gxx/*.cpp"
    "gxx/*/*.cpp"
)

set(SOURCE_LIB gxx/debug/dprint_stdout.c gxx/debug/dprint_func_impl.c ${SOURCE_LIB})

add_library(gxx STATIC ${SOURCE_LIB})