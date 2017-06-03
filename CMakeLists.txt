cmake_minimum_required(VERSION 2.8)																			
project(gxx)		

add_definitions(-std=gnu++14)
include_directories(".")

file(GLOB SOURCE_LIB
    "gxx/*.cpp"
    "gxx/*/*.cpp"
)


add_library(gxx STATIC ${SOURCE_LIB})