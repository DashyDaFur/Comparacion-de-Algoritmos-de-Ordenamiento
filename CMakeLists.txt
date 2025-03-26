cmake_minimum_required(VERSION 3.30)
project(ordenamiento)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-lpthread")
set(CMAKE_CXX_FLAGS_RELEASE "-O0")

add_executable(ordenamiento main.cpp)
