cmake_minimum_required(VERSION 3.7)
project(polylist)
file(GLOB SOURCES "*.cpp")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
include_directories(../common ../queue ../stack ../lists)
add_executable(polylist ${SOURCES})
