#  Project  Algorithms
# 
#  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>

cmake_minimum_required(VERSION 3.5)

project(algorithms CXX)

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS OFF)

include(cmake/Warnings.cmake)

add_subdirectory(src)
