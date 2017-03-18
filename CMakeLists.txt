cmake_minimum_required(VERSION 3.6)
project(Practical_13)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp Graph.h Graph.cpp)
add_executable(Practical_13 ${SOURCE_FILES})