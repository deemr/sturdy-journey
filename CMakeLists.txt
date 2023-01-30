cmake_minimum_required(VERSION 3.24)
project(kraken)

set(CMAKE_CXX_STANDARD 17)

add_executable(kraken main.cpp)

include_directories(/opt/homebrew/Cellar/boost/1.81.0_1/include/)
