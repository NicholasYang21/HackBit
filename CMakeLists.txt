cmake_minimum_required(VERSION 3.19)
project(HackBit)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-static ${CMAKE_CXX_FLAGS}")

add_executable(HackBit src/main.cpp include/functions/split.h include/os/user.h include/os/fs/fs.h src/os/fs/fs.cpp include/os/fs/file.h src/os/fs/file.cpp include/os/fs/directory.h src/os/fs/directory.cpp)