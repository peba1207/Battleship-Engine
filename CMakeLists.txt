cmake_minimum_required(VERSION 3.26)
project(battleship)

set(CMAKE_CXX_STANDARD 17)

add_executable(battleship main.cpp
        BoardState.cpp
        BoardState.h
        BoardCalculations.cpp
        BoardCalculations.h)
set(CMAKE_CXX_FLAGS "-Ofast")