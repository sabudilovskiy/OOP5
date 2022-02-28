cmake_minimum_required(VERSION 3.20)
project(OOP5)

set(CMAKE_CXX_STANDARD 20)
include_directories(includes)
add_executable(OOP5 main.cpp includes/Engine.h includes/Cargo.h includes/Planer.h includes/Support.h)
