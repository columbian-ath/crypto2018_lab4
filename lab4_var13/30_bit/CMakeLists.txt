cmake_minimum_required(VERSION 3.12)
project(30_bit)

set(CMAKE_CXX_STANDARD 14)

add_executable(30_bit main.cpp)
# added -fopenmp
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")
