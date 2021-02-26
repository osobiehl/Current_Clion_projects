cmake_minimum_required(VERSION 3.17)
project(untitled C)

set(CMAKE_C_STANDARD 99)
cmake_minimum_required(VERSION 2.8.9)
find_package(PkgConfig)
pkg_check_modules(LIBEVENT REQUIRED libevent)
include_directories(${LIBEVENT_INCLUDE_DIRS})
link_directories(${LIBEVENT_LIBRARY_DIRS})

add_executable(untitled main.c)
target_link_libraries(untitled ${LIBEVENT_LIBRARIES})