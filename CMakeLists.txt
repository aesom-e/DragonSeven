cmake_minimum_required(VERSION 3.22)
project(Baccarat)

set(CMAKE_CXX_STANDARD 23)

add_executable(Baccarat main.cpp
    deck.hpp
    shoe.hpp
    globals.hpp
    globals.cpp)