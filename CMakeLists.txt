cmake_minimum_required(VERSION 3.16)
project(hero)

set(CMAKE_CXX_STANDARD 11)

add_executable(hero src/main.cpp src/Battlefield.h src/Battlefield.cpp src/Unit.h src/Unit.cpp)