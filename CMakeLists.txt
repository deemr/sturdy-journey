cmake_minimum_required(VERSION 3.24)
project(kraken)
find_package(CURL REQUIRED)
add_executable(kraken main.cpp)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17") # enable C++17 standard


target_link_libraries(kraken CURL::libcurl)

