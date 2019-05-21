cmake_minimum_required(VERSION 3.14)
project(sim_cpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(sim_cpp main.cpp keyword.cpp keyword.h Lexer.cpp Lexer.h Cmp.h Cmp.cpp)