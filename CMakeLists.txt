# Project  Algorithms
#
# @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>

cmake_minimum_required(VERSION 3.19)

project(algorithms CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/Warnings.cmake)

add_subdirectory(src)
add_subdirectory(tests)
