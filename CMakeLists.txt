cmake_minimum_required(VERSION 3.30)
project(OrdenarDisc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++ -Wl,-Bstatic -lpthread -Wl,-Bdynamic")
set(CMAKE_CXX_FLAGS_RELEASE "-O0")

add_executable(OrdenarDisc main.cpp)
