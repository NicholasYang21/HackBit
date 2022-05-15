cmake_minimum_required(VERSION 3.19)
project(HackBit)

include_directories(frontend/tools/include)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-O2 -static ${CMAKE_CXX_FLAGS}")

add_executable(HackBit frontend/tools/include/stdfunc.hpp main.cc frontend/tools/source/stdfunc.cc frontend/tools/include/stdtype.hpp frontend/tools/include/hbstd.hpp)