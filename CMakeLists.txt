cmake_minimum_required(VERSION 3.19)
project(HackBit)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-static ${CMAKE_CXX_FLAGS}")

add_executable(HackBit Metta/src/game_main.cc Metta/include/filesystem.h Metta/src/filesystem.cc)